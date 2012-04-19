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
  Hrt::number varianceFilter;
  unsigned int maxPasses;

	bool ProcessCmdArgs( int argc, _TCHAR* * argv );
	std::string ReadSceneFile();
	bool LoadScene();
	void RenderScene();
	void ShowRendering(SDL_Surface* surface, int x, int y);
	bool ProcessPixelSampler(std::string& pixelSampler, unsigned rays);
	void ShowSettings();

	void ProcessKeyboard();
};
