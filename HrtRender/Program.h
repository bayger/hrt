/*
H-RT Renderer - a command-line raytracing renderer.
Copyright (c) Patryk Bajer, H-RT.

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
#include "../Core/Scene.h"
#include "../Core/Sampler.h"

class Program
{
public:
	Program(void);
	~Program(void);

	bool Initialize(int argc, _TCHAR* argv[]);
	void Run();

private:
	po::variables_map m_cmdArgs;
	Hrt::SceneOwnedPtr m_scene;
	unsigned int cpus;
	unsigned int rays;
	unsigned int depth;
	Hrt::number alpha;
	Hrt::number sigmaFilter;
	function<Hrt::SamplerOwnedPtr ()> m_pixelSamplerFactory;
	std::string pixelSamplerName;
	std::string pathDumpFileName;
	bool saveVariance;
	bool dontUseAdaptiveRR;
  bool whittedStyle;
  bool onlyPercentage;
  Hrt::number varianceFilter;
  unsigned int maxPasses;

	bool ProcessCmdArgs( int argc, _TCHAR* * argv );
	std::string ReadSceneFile();
	bool LoadScene();
	void RenderScene();
	void ShowRendering(SDL_Surface* surface, int x, int y);
	bool ProcessPixelSampler(std::string& pixelSampler, unsigned rays);
	void ShowSettings();
  std::string BuildParamNamePart();
	void ProcessKeyboard();
};
