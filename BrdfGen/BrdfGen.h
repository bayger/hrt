#include "stdafx.h"

class BrdfGen
{
public:
  bool Initialize(int argc, _TCHAR* argv[]);
  void Run();

private:
  po::variables_map m_cmdArgs;

};