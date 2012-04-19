/*
 * H-RT Core - the core of the H-RayTracer ray tracing renderer.
 * Copyright (c) 2006-2010 H-RT Team.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "stdafx.h"
#include "Renderer.h"
#include "Samplers\ConstSampler.h"
#include "Samplers\StratifiedSampler.h"
#include "Samplers\LhcSampler.h"
#include "Samplers\RandomSampler.h"

#include <iostream>
#include <fstream>
#include "RenderingContext.h"

namespace Hrt
{
	typedef function<bool (number& x, number& y)> RayFetchFunc;
	typedef function<void (int64 paths, int64 rejections)> NotifyFinishFunc;
	typedef function<void (const std::vector<Hrt::CanvasRay>& samples)> SavePathsFunc;

	// don't confuse this local struct with RenderingContext used globally
	struct RenderContext
	{
		size_t ThreadId;
		SceneOwnedPtr Scene;
		LightIntegratorOwnedPtr Integrator;
		CanvasOwnedPtr Canvas;
		CameraOwnedPtr Camera;
		function<SamplerOwnedPtr ()> PixelSamplerFactory;
		shared_array<number> VarianceTable;
		number SigmaFilter;
	};

	static void RenderThread(RenderContext context, NotifyFinishFunc notifyFinishFunc, RayFetchFunc rayFetchFunc, SavePathsFunc savePathsFunc)
	{
		Ray ray;
		number x, y;
		int64 rejections = 0, paths = 0;
		std::vector<Hrt::CanvasRay> canvasSamples;
		RandomizerOwnedPtr randomizer(new Randomizer());

		// per-level samplers
		int maxLevel = context.Integrator->GetMaxLevels();
		canvasSamples.reserve(maxLevel);
		std::vector<SamplerOwnedPtr> levelSamplers;

		// create all samplers (pixel and per-level)
		SamplerOwnedPtr pixelSampler(context.PixelSamplerFactory());
		for(int i=0; i<maxLevel; i++)
		{
			// NOTE: we are using LhcSampler for all levels
      auto pixelSamples = pixelSampler->GetCount();
			SamplerOwnedPtr sampler(pixelSamples > 1 
        ? (Sampler*)new LhcSampler(2, pixelSamples) 
        : (Sampler*)new ConstSampler(2));
			levelSamplers.push_back(sampler);
		}		

		// the rendering context
		RenderingContext rc(context.ThreadId, context.Canvas, randomizer, levelSamplers, context.Scene);

		// the render loop
		number pixel[2] = { 0 };
		while(rayFetchFunc(x, y))
		{
			Spectrum mean(0);

			rc.ShuffleLevelSamplers();

			pixelSampler->Shuffle(rc.GetRandomizer());
			canvasSamples.clear();
			while(pixelSampler->NextSample(pixel, rc.GetRandomizer()))
			{
				rc.NextLevelSamples();

				RayLight result;
				result.Radiance = 0;

				number canvasX, canvasY;
				context.Camera->ComputeRay(pixel, ray, canvasX, canvasY, (uint)x, (uint)y);
				context.Integrator->CalculateLight(ray, *(context.Scene), result, 0, rc);

				// omit invalid samples
				if (!_isnan(result.Radiance.GetAverage()))
					canvasSamples.push_back(Hrt::CanvasRay(canvasX, canvasY, result.Radiance, result.TotalDistance));
				else
					rejections++;

				mean += result.Radiance;
				paths++;
			}

			savePathsFunc(canvasSamples);

			if (canvasSamples.size() < 8 || context.SigmaFilter <= 0)
			{
				context.Canvas->CollectRays(canvasSamples);
			}
			else
			{
				mean /= canvasSamples.size();
				number ma = mean.GetAverage();

				// calculate standard deviation
				number sum = 0;
				for(size_t i=0; i<canvasSamples.size(); i++)
					sum += Math::Square(canvasSamples[i].Radiance.GetAverage() - ma);
				number sd = Math::Sqrt(sum / canvasSamples.size());

				// filter out extreme samples (deviation > 3*sd)
				for(size_t i=0; i<canvasSamples.size(); i++)
				{
					number sa = canvasSamples[i].Radiance.GetAverage();

					if (context.SigmaFilter <= 0 || Math::Abs(ma - sa) < context.SigmaFilter*sd)
						context.Canvas->CollectRay(canvasSamples[i].CanvasX, canvasSamples[i].CanvasY, canvasSamples[i].Radiance, canvasSamples[i].Depth);
					else
						rejections++;
				}

				context.VarianceTable[(int)x + context.Canvas->GetWidth()*(int)y] = sd / ma;
			}
		}

		// tell Renderer that this thread has just finished execution
		notifyFinishFunc(paths, rejections);
	}

	Renderer::Renderer(SceneOwnedPtr scene, CanvasPtr canvas, LightIntegratorPtr integrator, number sigmaFilter, size_t threadCount)	
	:	m_threadCount(threadCount),
		m_scene(scene),
		m_canvas(canvas),
		integrator(integrator),
		m_sigmaFilter(sigmaFilter),
		m_threadsRunning(0),
		m_x(-1), m_y(0),
		m_rejections(0),
		m_paths(0)
	{
	}

	void Renderer::Start(function<SamplerOwnedPtr ()> pixelSamplerFactory)
	{
		if (IsRendering())
			throw InvalidOperationException("The renderer is busy");

		m_stageSteps = m_canvas->GetWidth()*m_canvas->GetHeight();

		// open paths stream for writing
		if (IsRecordingPaths())
			m_recordingStream.reset(new std::ofstream(m_recordingFileName.c_str()));

		// create rendering threads
		m_threads.clear();
		m_threadsRunning = 0;
		m_rejections = 0;
		m_paths = 0;
		m_varianceTable.reset(new number[m_canvas->GetWidth() * m_canvas->GetHeight()]);
		lock_guard<mutex> syncLock(m_syncMutex);
		for(size_t i=0; i<m_threadCount; i++)
		{
			m_threadsRunning++;
			NotifyFinishFunc ntf = bind(&Renderer::NotifyThreadFinished, this, _1, _2);
			RayFetchFunc pfc = bind(&Renderer::GetNextPixel, this, _1, _2);
			SavePathsFunc spf = boost::bind(&Renderer::SavePaths, this, _1);

			RenderContext rc;
			rc.ThreadId = i;
			rc.Camera = m_scene->GetCamera();
			rc.Canvas = m_canvas;
			rc.Integrator = integrator;
			rc.PixelSamplerFactory = pixelSamplerFactory;
			rc.Scene = m_scene;
			rc.VarianceTable = m_varianceTable;
			rc.SigmaFilter = m_sigmaFilter;

			thread* t = new thread(&RenderThread, rc, ntf, pfc, spf);
			m_threads.push_back(shared_ptr<thread>(t));
		}
	}

	void Renderer::WaitUntilFinished()
	{
		if (!IsRendering())
			return;

		for(size_t i=0; i<m_threads.size(); i++)
			m_threads[i]->join();
	}

	number Renderer::GetProgress()
	{
		int w = m_canvas->GetWidth();
		int h = m_canvas->GetHeight();
		return num( m_x + m_y*w ) / (w*h);
	}

	bool Renderer::IsRendering()
	{
		return m_threadsRunning > 0;
	}

	void Renderer::NotifyThreadFinished(int64 paths, int64 rejections)
	{
		lock_guard<mutex> syncLock(m_syncMutex);
		m_threadsRunning--;
		m_rejections += rejections;
		m_paths += paths;

		if (m_threadsRunning == 0)
			m_recordingStream.reset();
	}

	bool Renderer::GetNextPixel(number& x, number& y)
	{
		if (m_y >= num(m_canvas->GetHeight()))
			return false;

		lock_guard<mutex> syncLock(m_getPixelMutex);

		m_x++;
		if (m_x == m_canvas->GetWidth())
		{
			m_x = 0;
			m_y++;
		}
		if (m_y == m_canvas->GetHeight())
			return false;

		x = m_x;
		y = m_y;

		return true;
	}

	void Renderer::GetCurrentPixel(int& x, int& y)
	{
		x = m_x;
		y = m_y;
	}

	void Renderer::SavePaths(const std::vector<Hrt::CanvasRay>& samples)
	{
		if (!IsRecordingPaths() || m_recordingStream == 0)
			return;

		lock_guard<mutex> syncLock(m_saveMutex);
		for(std::vector<Hrt::CanvasRay>::const_iterator it = samples.begin(); it != samples.end(); it++)
		{
			*m_recordingStream << it->CanvasX << " " << it->CanvasY << " " << it->Depth;
			for(int i=0; i<Spectrum::LambdaCount; i++)
				*m_recordingStream << " " << it->Radiance.Values[i];
			*m_recordingStream << std::endl;
		}
	}
}