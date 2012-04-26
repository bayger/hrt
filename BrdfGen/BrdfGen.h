#include "stdafx.h"
#include "..\Core\Scene.h"

class BrdfGen
{
public:
  bool Initialize(int argc, _TCHAR* argv[]);
  void Run();

private:
  po::variables_map m_cmdArgs;
  Hrt::SceneOwnedPtr m_scene;
  Hrt::MaterialOwnedPtr m_material;
  Hrt::number m_step;

  std::string LoadScene();
  void OutputData();
};