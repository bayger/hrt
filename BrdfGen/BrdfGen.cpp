// BrdfGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Core\Common.h"
#include "BrdfGen.h"
#include "..\Core\Serialization\YamlParser.h"
#include "..\Core\Serialization\SerializationContext.h"
#include "..\Core\Math.h"
#include "..\Core\Vector3D.h"

using namespace Hrt;

bool BrdfGen::Initialize(int argc, _TCHAR* argv[]) 
{
  po::positional_options_description args;
  args.add("scene-file", 1);
  args.add("material-name", 1);

  Hrt::number step = 0.1;
  Hrt::number incidentAngle = 30;
  po::options_description options("options");
  options.add_options()
    ("help", "shows this help")
    ("about", "shows information about this program")
    ("version,v", "shows version number of H-RayTracer")
    ("step,s", po::value<Hrt::number>(&step), "sets angle step for generated series [0.1]")
    ("incident,i", po::value<Hrt::number>(&incidentAngle), "sets incident angle for generated series [30]")
    ("materials", "outputs only material names (line by line)");
  
  po::options_description hidden("hidden");
  hidden.add_options()
    ("scene-file", "scene file (YSF format)")
    ("material-name", "name of material in the scene");

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
    std::cout << std::endl << "usage: brdfgen [options] scene-file material-name" 
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

  if (((m_cmdArgs.count("scene-file") == 0 || m_cmdArgs.count("material-name") == 0) && !m_materialsOnly) || !argsProcessed)
  {
    std::cout << "Invalid number of arguments. Use '--help' option to get detailed help."
      << std::endl;
    return false;
  }

  m_step = m_cmdArgs.count("steps") > 0 ? step : 0.1;
  m_materialsOnly = m_cmdArgs.count("materials") > 0;
  m_incidentAngle = incidentAngle;
  return true;
}

std::string BrdfGen::LoadScene()
{
  std::string brdfFileName = m_cmdArgs["scene-file"].as<std::string>();
  std::cout << "Input: " << brdfFileName << std::endl;
  std::ifstream sceneFile(brdfFileName.c_str());

  sceneFile.seekg(0, std::ios_base::end);
  long int size = sceneFile.tellg();
  sceneFile.seekg(0, std::ios_base::beg);
  scoped_array<char> buffer(new char[size+1]);
  memset(buffer.get(), 0, sizeof(char)*(1+size));
  sceneFile.read(buffer.get(), size);

  YamlParser parser(std::string(buffer.get()));
  m_scene.reset(new Scene);

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
}

void BrdfGen::Run()
{
  LoadScene();

  if (m_materialsOnly)
    OutputMaterialNames();
  else
  {
    std::string materialName = m_cmdArgs["material-name"].as<std::string>();
    m_material = m_scene->GetMaterial(materialName);
    if (m_material != NULL)
      OutputData();
  }
}

void BrdfGen::OutputData()
{
  std::cout << "# Material: " << m_material->GetName() << std::endl;
  std::cout << "# Signature: " << m_material->GetSignature() << std::endl;
  
  RayLight rayLight;
  rayLight.Direction = -Vector3D::FromSpherical(0, Consts::Pi / 180 * m_incidentAngle);
  rayLight.Radiance.SetOne();
  for(number angle=-90; angle<90.0; angle += m_step)
  {
    Intersection intersection;
    intersection.Normal = Vector3D::UnitZ;
    intersection.Position.Set(0, 0, 0);
    intersection.TangentU = Vector3D::UnitX;
    intersection.TangentV = Vector3D::UnitY;
    intersection.RayDirection = -Vector3D::FromSpherical(angle < 0 ? Consts::Pi : 0, 
      Math::Abs(angle) / 180 * Consts::Pi);

    Spectrum x = m_material->CalculateBsdf(rayLight, intersection);
    std::cout << m_incidentAngle << "\t" << angle;
    for(int i=0; i<Spectrum::LambdaCount; i++)
    {
      std::cout << "\t" << x[i];
    }
    std::cout << std::endl;
  }
}

void BrdfGen::OutputMaterialNames()
{
  std::cout << "# Materials" << std::endl;
  auto materials = m_scene->GetAllMaterials();
  for(auto kv = materials.begin(); kv != materials.end(); kv++)
  {
    std::cout << kv->second->GetName() << "\t" << kv->second->GetSignature() << std::endl;
  }
}

int _tmain(int argc, _TCHAR* argv[])
{
  BrdfGen application;
  if (!application.Initialize(argc, argv))
    return -1;

  application.Run();
  return 0;
}

