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

#include "Scene.h"
#include "LightIntegrator.h"

namespace Hrt
{
	/// A multi-threaded scene renderer
	class Renderer
	{
	public:
		/// Creates multi-threaded scene renderer.
		/// \note The size of instances vector determines the number of rendering threads. Make sure that all instances contain the same scene data.
		Renderer(SceneOwnedPtr scene, CanvasPtr canvas, LightIntegratorPtr integrator, number sigmaFilter, size_t threadCount, number varianceFilter, int maxPasses);

		/// Starts rendering using provided pixel sampler factory
		/// \note This factory will be also used for creating per-level path randomizers
		void Start(function<SamplerOwnedPtr ()> pixelSamplerFactory);
		
		/// Cancels rendering
		void Abort();

		/// Returns a number in range [0..1] representing rendering progress
		number GetProgress();

		/// Blocks current thread until rendering is finished
		void WaitUntilFinished();

		/// Returns true if rendering is in progress
		bool IsRendering();

		/// Since Renderer is only 1-pass algorithm it always returns 0
		int GetCurrentPass() { return 0; }
		
		/// Gets the currently computed pixel (recently fetched by one of the rendering threads)
		void GetCurrentPixel(int& x, int& y);

		/// Returns the number of filtered out paths
		/// \note This value is not updated during rendering. Read it after the rendering is finished.
		int64 GetRejectionCount() { return m_rejections; }

		/// Returns the total number of computed paths
		/// \note This value is not updated during rendering. Read it after the rendering is finished.
		int64 GetPathCount() { return m_paths; }

		/// Returns the variance table that contains Sqrt(variance) of samples for each pixel
		/// \note Returned table has the same size as the canvas used for rendering
		shared_array<number> GetVarianceTable() { return m_varianceTable; }

		/// Enables saving of all computed paths to a text file
		void EnablePathsRecording(const std::string& fileName) { m_recordingFileName = fileName; }

		/// Disables paths saving feature
		void DisablePathsRecording() { m_recordingFileName.clear(); }

		/// Returns true if paths saving feature is enabled
		bool IsRecordingPaths() { return !m_recordingFileName.empty(); }

		/// Returns the paths recording file name
		const std::string& GetPathsRecording() { return m_recordingFileName; }

	private:
		size_t m_threadCount;
		SceneOwnedPtr m_scene;
		CanvasOwnedPtr m_canvas;
		number m_sigmaFilter;
		int m_stageSteps, m_x, m_y;
		std::vector<shared_ptr<thread>> m_threads;
		LightIntegratorOwnedPtr integrator;
		mutex m_syncMutex;
		mutex m_getPixelMutex;
		mutex m_saveMutex;
		int m_threadsRunning;
		int64 m_rejections;
		int64 m_paths;
		shared_array<number> m_varianceTable;
		std::string m_recordingFileName;
		shared_ptr<std::ofstream> m_recordingStream;
    number m_varianceFilter;
    int m_maxPasses;

		void NotifyThreadFinished(int64 paths, int64 rejections);
		bool GetNextPixel(number& x, number& y);
		void SavePaths(const std::vector<Hrt::CanvasRay>& samples);
	};

}