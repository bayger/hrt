/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-2010 H-RT Team.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#pragma once
#include "Common.h"
#include "Canvas.h"
#include "Random.h"
#include "Sampler.h"

namespace Hrt
{
  class Light;
  class Scene;

	/// Per-thread rendering context containing common objects used in rendering.
	class RenderingContext
	{
	public:
		RenderingContext(size_t threadId, CanvasPtr canvas, RandomizerPtr randomizer, std::vector<SamplerOwnedPtr> levelSamplers, shared_ptr<Scene>& scene);

		CanvasPtr GetCanvas() { return m_canvas; }

		size_t GetThreadId() { return m_threadId; }

		RandomizerPtr GetRandomizer() { return m_randomizer; }

		std::vector<number>& GetLevelSamples() { return m_levelSamples; }

    std::vector<shared_ptr<Light>> GetLights() { return m_lights; }

		void ShuffleLevelSamplers();

		void NextLevelSamples();

	private:
		size_t m_threadId;
		CanvasOwnedPtr m_canvas;
		RandomizerOwnedPtr m_randomizer;
		std::vector<number> m_levelSamples;
		std::vector<SamplerOwnedPtr> m_levelSamplers;
    std::vector<shared_ptr<Light>> m_lights;
	};

}