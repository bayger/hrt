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
#include "stdafx.h"
#include "Program.h"
#include "../Core/HrtCore.h"
#include "Utils.h"
#include "../Core/Renderer.h"
#include "../Tools/HdrCodec.h"

using namespace Hrt;

Program::Program(void)
: cpus(1), saveVariance(false), dontUseAdaptiveRR(false)
{
	FreeImage_Initialise();
}

Program::~Program(void)
{
	FreeImage_DeInitialise();
}

void Program::Run()
{
	if (!LoadScene())
		return;

	// start rendering
	RenderScene();
}

bool Program::Initialize(int argc, _TCHAR* argv[])
{
	std::cout << "H-RayTracer Rendering Tool."
		<< std::endl;

	return ProcessCmdArgs(argc, argv);
}

bool Program::ProcessCmdArgs( int argc, _TCHAR* * argv )
{
	unsigned int cpus = 1;
	unsigned int rays = 16;
	unsigned int depth = 12;
	number alpha = 0.1;
	number sigmaFilter = 0;
	std::string pixelSampler;
	std::string pathDumpFileName;
  number varianceFilter = 0;
  unsigned int maxPasses = 16;

	po::positional_options_description args;
	args.add("scene-file", 1);
	args.add("output-file", 1);

	po::options_description options("options");
	options.add_options()
		("help", "shows this help")
		("about", "shows information about this program")
		("version,v", "shows version number of H-RayTracer")
		("threads,t", po::value<unsigned int>(&cpus), "sets number of rendering threads [1]")
		("depth,d", po::value<unsigned int>(&depth), "sets max depth of each path [12]")
		("alpha,a", po::value<number>(&alpha), "sets alpha value for Russian Roulette [adaptive]")
		("paths,r", po::value<unsigned int>(&rays), "sets number of paths per pixel [16]")
		("pixel-sampler,p", po::value<std::string>(&pixelSampler), "pixel sampler: random, lhc, stratified [auto]")
		("sigma-filter", po::value<number>(&sigmaFilter), "sigma filter value [disabled=0]")
    ("variance-filter", po::value<number>(&varianceFilter), "variance filter value [disabled=0]")
    ("variance-max-passes", po::value<unsigned int>(&maxPasses), "max passes for variance filtering [16]")
		("dump-paths", po::value<std::string>(&pathDumpFileName), "dumps all paths to a file [disabled]")
		("save-variance", "saves also per-pixel path variance [disabled]")
    ("whitted,w", "switches to simple Whitted-style raytracing")
    ("percentage", "displays only percentage line-by-line");

	po::options_description hidden("hidden");
	hidden.add_options()
		("scene-file", "input scene file name")
		("output-file", "output image file name");

	po::options_description all("all options");
	all.add(options).add(hidden);

	bool argsProcessed = false;
	try
	{
		po::store(po::basic_command_line_parser<TCHAR>(argc, argv).options(all)
			.positional(args).run(), m_cmdArgs);
		po::notify(m_cmdArgs);
		argsProcessed = true;
	}
	catch(...) { }

	if (!ProcessPixelSampler(pixelSampler, rays))
	{
		std::cout << std::endl << "Invalid pixel sampler. Use random, lhc or stratified." << std::endl;
		return false;
	}

	if (m_cmdArgs.count("alpha"))
	{
		dontUseAdaptiveRR = true;
	}

	if (m_cmdArgs.count("help"))
	{
		std::cout << std::endl << "usage: hrtrender [options] scene-file output-file" 
			<< std::endl << std::endl;
		std::cout << options << std::endl;
		return false;
	}
	else if (m_cmdArgs.count("about"))
	{
		std::cout << std::endl << "H-RayTracer is developed by Patryk Bajer under the GNU General Public License." << std::endl << std::endl;
		std::cout << "This software uses the FreeImage open source image library. See http://freeimage.sourceforge.net for details. ";
		std::cout << "FreeImage is used under the GNU GPL, version 2. " << std::endl << std::endl;
		std::cout << "This software uses the SDL open source media library. See http://www.libsdl.org for details. ";
		std::cout << "SDL is used under the GNU LGPL. " << std::endl << std::endl;
		std::cout << "This software uses the GNU Scientific Library. See http://www.gnu.org/software/gsl for details. ";
		std::cout << "GSL is used under the GNU GPL, version 3. " << std::endl << std::endl;
		return false;
	}
	else if (m_cmdArgs.count("version"))
	{
		std::cout << Hrt::LibraryInfo::GetFullName() << std::endl;
		return false;
	}

	if (m_cmdArgs.count("scene-file") == 0 || !argsProcessed)
	{
		std::cout << "Invalid number of arguments. Use '--help' option to get detailed help."
			<< std::endl;
		return false;
	}

	this->cpus = (cpus < 1) ? 1 : cpus;
	this->rays = (rays < 1) ? 1 : rays;
	this->depth = depth;
	this->alpha = alpha > 0 && alpha < 1 ? alpha : 0.1;
	this->sigmaFilter = sigmaFilter;
	this->pathDumpFileName = pathDumpFileName;
	this->saveVariance = m_cmdArgs.count("save-variance") > 0;
  this->whittedStyle = m_cmdArgs.count("whitted") > 0;
  this->onlyPercentage = m_cmdArgs.count("percentage") > 0;
  this->varianceFilter = varianceFilter;
  this->maxPasses = maxPasses;
	return true;
}

std::string Program::ReadSceneFile()
{
	std::string sceneFileName = m_cmdArgs["scene-file"].as<std::string>();
	std::cout << "Input: " << sceneFileName << std::endl;
	std::ifstream sceneFile(sceneFileName.c_str());

	sceneFile.seekg(0, std::ios_base::end);
	long int size = sceneFile.tellg();
	sceneFile.seekg(0, std::ios_base::beg);
	scoped_array<char> buffer(new char[size+1]);
	memset(buffer.get(), 0, sizeof(char)*(1+size));
	sceneFile.read(buffer.get(), size);

	return std::string(buffer.get());
}

bool Program::LoadScene()
{
	m_scene.reset(new Scene);

	YamlParser parser(ReadSceneFile());

	try
	{
		SerializationContext context;
		m_scene->Deserialize(parser, context);
	}
	catch (SerializationException& e)
	{
		std::cout << "Failed to read scene file." << std::endl
			<< "Error: " << e.GetMessage() << std::endl;
		return false;
	}

	return true;
}

void write_time(double seconds)
{
	int sec = (int)floor(seconds);
	int h = sec / 3600;
	int m = (sec % 3600) / 60;
	int s = sec % 60;

	std::cout << (format("%|1$3d|:%|2$02d|:%|3$02d|") % h % m % s);
}

void Program::RenderScene()
{
	char spinner[] = {'/' , '-', '\\', '|' };
	CanvasPtr canvas = m_scene->GetCanvas();

	ShowSettings();

	// we'll use path tracing integrator
	LightIntegratorOwnedPtr integrator = whittedStyle 
    ? LightIntegratorOwnedPtr(new DeterministicIntegrator(depth))
    : LightIntegratorOwnedPtr(new PathTracingIntegrator(depth, depth > 3 ? 3 : depth, dontUseAdaptiveRR ? alpha : -1));

	// prepare scene for concurrency
	m_scene->PrepareForConcurrency(cpus);

	// create renderer
	Renderer renderer(m_scene, m_scene->GetCanvas(), integrator, sigmaFilter, cpus, varianceFilter, maxPasses);
	if (!pathDumpFileName.empty())
		renderer.EnablePathsRecording(pathDumpFileName);

	int i = 0;
	unsigned int currentStage = 0;
	number progress = 0;

	timer elapsedTimer;
	elapsedTimer.restart();

	renderer.Start(m_pixelSamplerFactory);

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* surface = SDL_SetVideoMode(canvas->GetWidth(), canvas->GetHeight(), 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("Rendering in progress...", NULL);

	do 
	{
		boost::xtime xt;
		boost::xtime_get(&xt, boost::TIME_UTC);
		xt.nsec += 100000000;
		boost::thread::sleep(xt);

		progress = renderer.GetProgress();
		double seconds = elapsedTimer.elapsed();

		std::string caption = str( format("Rendering %|1$.2f|%% complete - pass: %2%") % (100.*progress) % (renderer.GetCurrentPass()+1) );
		SDL_WM_SetCaption(caption.c_str(), NULL);

    if (onlyPercentage)
    {
      std::cout << "Completed: " << std::fixed << std::setprecision(2)
        << (100.*progress) << std::endl;
    }
    else
    {
		  std::cout << "Rendering" << " [" << std::fixed << std::setprecision(2)
			  << (100.*progress)
			  << "% complete]... " << spinner[i % 4] << " Elapsed: "; 

		  write_time(seconds);
		  std::cout << "  Estimated: ";
		  write_time(seconds/progress);
		  std::cout << "     \r";
    }

		i++;

		if (i % 10 == 0)
		{
			int cx, cy;
			renderer.GetCurrentPixel(cx, cy);
			ShowRendering(surface, cx, cy);
		}
		
		ProcessKeyboard();

	} while(renderer.IsRendering());
	
	//shared_ptr<PathTracingIntegrator> pti = dynamic_pointer_cast<PathTracingIntegrator>(integrator);
	//int64 calculationCount = pti->GetCalculationCount();
	//int64 pathCount = pti->GetPathCount();
	int64 rejections = renderer.GetRejectionCount();
	number percRejections = num(rejections) / renderer.GetPathCount() * 100;

	std::cout << std::endl;
	//std::cout << "Total ray calculations: " << calculationCount << std::endl;
	//std::cout << "Average path length: " << num(calculationCount)/pathCount << std::endl;
	//std::cout << "Total paths: " << renderer.GetPathCount() << " " << pathCount << std::endl;
	std::cout << "Total rejections: " << renderer.GetRejectionCount() << " (" << std::setprecision(2) << percRejections << "%)" << std::endl;
	std::cout << "Rendering complete." << std::endl;

	Hrt::Tools::HdrCodec codec;
	boost::posix_time::ptime now(boost::date_time::microsec_clock<
		boost::posix_time::ptime>::local_time());

	std::string outputFileName = m_cmdArgs["output-file"].empty() 
		? m_cmdArgs["scene-file"].as<std::string>() + 
			str(format(".%1%%2%%3%_%|4$02d|%|5$02d|") % now.date().year() % now.date().month()
			% now.date().day() % now.time_of_day().hours() % now.time_of_day().minutes())
		: m_cmdArgs["output-file"].as<std::string>();

	{
		ImageOwnedPtr image = m_scene->GetCanvas()->GenerateImage();
		codec.SaveImage(image, outputFileName + ".hdr");
		std::cout << "Rendering saved as " << outputFileName + ".hdr" << std::endl;
	}

	if (saveVariance)
	{
		uint w = canvas->GetWidth();
		uint h = canvas->GetHeight();
		shared_array<number> varianceTable = renderer.GetVarianceTable();
		ImageOwnedPtr varianceImage(new Image(w, h));
		Hrt::CieXyz* pixels = varianceImage->GetPixels();
		for(size_t i=0; i<w*h; i++)
			pixels[i].X = pixels[i].Y = pixels[i].Z = varianceTable[i];
		codec.SaveImage(varianceImage, outputFileName + ".variance.hdr");
		std::cout << "Variance saved as " << outputFileName + ".variance.hdr" << std::endl;
	}
}


void DrawImage(SDL_Surface* screen, FIBITMAP* bitmap, int w, int h, int ch, int render_y)
{
	if ( SDL_MUSTLOCK(screen) ) 
	{
		if ( SDL_LockSurface(screen) < 0 ) 
			return;
	}

	Uint32 *bufp;

	for(int y=0; y<h; y++)
	{
		unsigned char* scanline = (unsigned char*)FreeImage_GetScanLine(bitmap, y);
		for(int x=0; x<w; x++)
		{
			unsigned color = (h-1 != y) 
				? ((*((unsigned*)&scanline[x*3])) & 0xffffff) 
				: 0xffffff;
			bufp = (unsigned*)screen->pixels + (ch-y-1)*screen->pitch/4 + x;
			*bufp = color;
		}
	}

	if ( SDL_MUSTLOCK(screen) ) {
		SDL_UnlockSurface(screen);
	}
	SDL_UpdateRect(screen, 0, 0, w, ch);
}



void Program::ShowRendering(SDL_Surface* surface, int cx, int cy)
{
	CanvasPtr canvas = m_scene->GetCanvas();
	ImageOwnedPtr image = canvas->GenerateImage();

	CieXyz* pixels = image->GetPixels();
  uint h = cy;
	FIBITMAP* bitmap = FreeImage_AllocateT(FIT_RGBF, image->GetWidth(), h);
	int i = 0;
	for(uint y=0; y<h; y++)
	{
		float* scanline = (float*)FreeImage_GetScanLine(bitmap, y);
		for(uint x=0; x<image->GetWidth(); x++)
		{
			Rgb color;
			color.FromCieXyz(pixels[i]);

			scanline[x*3 + 0] = (float)color.R;
			scanline[x*3 + 1] = (float)color.G;
			scanline[x*3 + 2] = (float)color.B;

			i++;
		}
	}

	FIBITMAP* trueColorBitmap = FreeImage_ToneMapping(bitmap, FITMO_REINHARD05);

	DrawImage(surface, trueColorBitmap, image->GetWidth(), h, image->GetHeight(), cy);

	FreeImage_Unload(trueColorBitmap);
	FreeImage_Unload(bitmap);
}

static SamplerOwnedPtr CreateRandomSampler(int sampleCount)
{
	return SamplerOwnedPtr(new RandomSampler(2, sampleCount));
}

static SamplerOwnedPtr CreateStratifiedSampler(int strataCount)
{
	return SamplerOwnedPtr(new StratifiedSampler(2, strataCount));
}

static SamplerOwnedPtr CreateLhcSampler(int sampleCount)
{
	return SamplerOwnedPtr(new LhcSampler(2, sampleCount));
}

static SamplerOwnedPtr CreateUniformSampler()
{
  return SamplerOwnedPtr(new ConstSampler(2));
}

bool Program::ProcessPixelSampler(std::string& pixelSampler, unsigned rays)
{
	if (pixelSampler.empty())
	{
		number raysSqrt = Math::Sqrt(rays);
		pixelSampler = (raysSqrt == Math::Floor(raysSqrt)) ? "stratified" : "lhc";
	}

	if (pixelSampler == "random")
	{
		m_pixelSamplerFactory = bind(&CreateRandomSampler, rays);
		pixelSamplerName = "Uniform Random";
		return true;
	}
	else if (pixelSampler == "lhc")
	{
		m_pixelSamplerFactory = bind(&CreateLhcSampler, rays);
		pixelSamplerName = "Latin Hyper Cube";
		return true;
	}
	else if (pixelSampler == "stratified")
	{
		int strataCount = (int)Math::Sqrt(rays);
		m_pixelSamplerFactory = bind(&CreateStratifiedSampler, strataCount);
		pixelSamplerName = "Stratified";
		return true;
	}
  else if (pixelSampler == "const")
  {
    m_pixelSamplerFactory = bind(&CreateUniformSampler);
    pixelSamplerName = "Const";
    return true;
  }

	return false;
}

void Program::ProcessKeyboard()
{
	SDL_Event event;

	while( SDL_PollEvent( &event ) )
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch( event.key.keysym.sym )
			{
			case SDLK_ESCAPE:
				std::cout << std::endl << "Rendering aborted." << std::endl;
				exit(1);
				break;
			}
		}
	}
}

void Program::ShowSettings()
{
	std::cout << std::endl;
	std::cout << "    Pixel sampler: " << pixelSamplerName << std::endl;
	std::cout << "  Paths per pixel: " << rays << std::endl;
	std::cout << "Max depth of path: " << depth << std::endl;
	std::cout << "   RR Alpha value: ";
	if (dontUseAdaptiveRR)
		std::cout << std::setprecision(2) << alpha << std::endl;
	else
		std::cout << "adaptive" << std::endl;
	std::cout << "     Sigma filter: " << std::setprecision(2) << sigmaFilter << std::endl;
	std::cout << "Rendering threads: " << cpus << std::endl << std::endl;
}
