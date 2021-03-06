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
  Hrt::number outgoingAngle = 30;
  po::options_description options("options");
  options.add_options()
    ("help", "shows this help")
    ("about", "shows information about this program")
    ("version,v", "shows version number of H-RayTracer")
    ("step,s", po::value<Hrt::number>(&step), "sets angle step for generated series [0.1]")
    ("outgoing,o", po::value<Hrt::number>(&outgoingAngle), "sets outgoing angle for generated series [30]")
    ("pdf,p", "outputs PDF instead of BRDF")
    ("precalc-all", "precalculates all materials in the scene")
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

  if (((m_cmdArgs.count("scene-file") == 0 || m_cmdArgs.count("material-name") == 0) 
    && m_cmdArgs.count("materials") == 0 && m_cmdArgs.count("precalc-all") == 0) || !argsProcessed)
  {
    std::cerr << "Invalid number of arguments. Use '--help' option to get detailed help."
      << std::endl;
    return false;
  }

  m_step = m_cmdArgs.count("step") > 0 ? step : 0.1;
  m_materialsOnly = m_cmdArgs.count("materials") > 0;
  m_outputPdf = m_cmdArgs.count("pdf") > 0;
  m_precalcAll = m_cmdArgs.count("precalc-all") > 0;
  m_outgoingAngle = outgoingAngle;
  return true;
}

void BrdfGen::LoadScene()
{
  std::string brdfFileName = m_cmdArgs["scene-file"].as<std::string>();
  std::ifstream sceneFile(brdfFileName.c_str());

  sceneFile.seekg(0, std::ios_base::end);
  long int size = static_cast<long int>(sceneFile.tellg());
  if (size == -1)
  {
    std::cerr << "Scene file not found" << std::endl;
    return;
  }
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
    std::cerr << "Failed to read scene file." << std::endl
      << "Error: " << e.GetMessage() << std::endl;
    m_scene.reset();
  }
}

void BrdfGen::Run()
{
  LoadScene();
  if (m_scene == NULL)
    return;

  if (m_materialsOnly)
    OutputMaterialNames();
  else
  {
    if (m_precalcAll)
      PrecalcAllMaterials();
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
  
  m_material->Initialize();
  
  std::cout << "AngleR\tAngleI";
  for(int i=0; i<Spectrum::LambdaCount; i++)
  {
    std::cout << "\tF(lambda=" << Spectrum::IndexToLambda(i) << ")";
  }
  std::cout << std::endl;

  Intersection intersection;
  intersection.Normal = Vector3D::UnitZ;
  intersection.Position.Set(0, 0, 0);
  intersection.TangentU = Vector3D::UnitX;
  intersection.TangentV = Vector3D::UnitY;
  intersection.RayDirection = -Vector3D::FromSpherical(0, Consts::Pi / 180 * m_outgoingAngle);

  for(number angle=-90; angle<90.0; angle += m_step)
  {
    RayLight rayLight;
    rayLight.Direction = -Vector3D::FromSpherical(angle < 0 ? Consts::Pi : 0, 
      Math::Abs(angle) / 180 * Consts::Pi);
    rayLight.Radiance.SetOne();

    bool isInSpecularCone = Math::Abs(angle + m_outgoingAngle) < epsilon;

    std::cout << m_outgoingAngle << "\t" << angle;

    if (m_outputPdf)
    {
      Hrt::number pdf = m_material->CalculatePdf(-intersection.RayDirection,
        intersection.TangentU, 
        intersection.TangentV, 
        intersection.Normal, 
        rayLight.Direction, 
        static_cast<LightingType::Enum>(LightingType::AllReflection | (isInSpecularCone ? LightingType::IdealSpecular : 0)));
      std::cout << "\t" << pdf;
    }
    else
    {
      Spectrum x = m_material->CalculateBrdf(rayLight, intersection, 
        static_cast<LightingType::Enum>(LightingType::AllReflection | (isInSpecularCone ? LightingType::IdealSpecular : 0)));
      for(int i=0; i<Spectrum::LambdaCount; i++)
      {
        std::cout << "\t" << x[i];
      }
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

void BrdfGen::PrecalcAllMaterials()
{
  for(auto it = m_scene->GetAllMaterials().begin(); it != m_scene->GetAllMaterials().end(); it++)
    it->second->Initialize();
}

int _tmain(int argc, _TCHAR* argv[])
{
  BrdfGen application;
  if (!application.Initialize(argc, argv))
    return -1;

  application.Run();
  return 0;
}

