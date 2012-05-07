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
  bool m_materialsOnly;
  bool m_outputPdf;
  bool m_precalcAll;
  Hrt::number m_incidentAngle;
  void LoadScene();
  void OutputData();
  void OutputMaterialNames();
  void PrecalcAllMaterials();
};