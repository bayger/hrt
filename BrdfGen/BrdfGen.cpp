// BrdfGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Core\Common.h"
#include "BrdfGen.h"

using namespace Hrt;

bool BrdfGen::Initialize(int argc, _TCHAR* argv[]) 
{
  po::positional_options_description args;
  args.add("brdf-name", 1);
  args.add("output-type", 1);

  Hrt::number step = 0.1;
  po::options_description options("options");
  options.add_options()
    ("help", "shows this help")
    ("about", "shows information about this program")
    ("version,v", "shows version number of H-RayTracer")
    ("step,s", po::value<Hrt::number>(&step), "sets angle step for generated series [0.1]");
  
  po::options_description hidden("hidden");
  hidden.add_options()
    ("brdf-name", "used brdf")
    ("output-type", "type of output series");

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

  if (m_cmdArgs.count("help"))
  {
    std::cout << std::endl << "usage: brdfgen [options] brdf-type output-type" 
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

  if (m_cmdArgs.count("brdf-name") == 0 || m_cmdArgs.count("output-type") == 0 || !argsProcessed)
  {
    std::cout << "Invalid number of arguments. Use '--help' option to get detailed help."
      << std::endl;
    return false;
  }

  return true;
}

void BrdfGen::Run()
{
  std::cout << "fuck";
}

int _tmain(int argc, _TCHAR* argv[])
{
  BrdfGen application;
  if (!application.Initialize(argc, argv))
    return -1;

  application.Run();
  return 0;
}

