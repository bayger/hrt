/*
 * H-RT Core - the core of the H-RayTracer ray tracing renderer.
 * Copyright (c) Patryk Bajer, H-RT.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "stdafx.h"
#include "LipisSerializer.h"
#include <iostream>
#include <fstream>

namespace Hrt
{
  const char fileHeader[] = "!ISF";

  struct ImportanceSamplingFileHeader
  {
    char IDTag[4];
    short int MajorVersion;
    short int MinorVersion;
    int ElevationSteps;
    int AzimuthSteps;
    char Reserved[16];

    ImportanceSamplingFileHeader(size_t elevationSteps, size_t azimuthSteps) 
    {
      std::fill(&Reserved[0], &Reserved[16], 0);
      std::copy(&fileHeader[0], &fileHeader[4], &IDTag[0]);
      MajorVersion = 1;
      MinorVersion = 0;
      ElevationSteps = elevationSteps;
      AzimuthSteps = azimuthSteps;
    }

    bool operator ==(const ImportanceSamplingFileHeader& other) const
    {
      return MajorVersion == other.MajorVersion
        && MinorVersion == other.MinorVersion
        && std::equal(&IDTag[0], &IDTag[4], &other.IDTag[0])
        && ElevationSteps == other.ElevationSteps
        && AzimuthSteps == other.AzimuthSteps;
    }

    bool operator !=(const ImportanceSamplingFileHeader& other) const
    {
      return !(*this == other);
    }
  };

  static std::string SignatureToFilename(const std::string& signature, const std::string& ext)
  {
    size_t p = std::string::npos;
    std::string fn(signature);

    while ((p = fn.find_first_of(':')) != std::string::npos)
      fn[p] = '-';

    return fn + ext;
  }

  void LipisSerializer::Save(std::string materialSignature, 
    size_t elevationCount,
    size_t azimuthCount,
    std::vector<shared_ptr<Lipis::LipisAngleData>>& angleData)
  {
    std::string fileName = SignatureToFilename(materialSignature, ".isf");

    std::cout << "Writing " << fileName << std::endl;

    std::ofstream outFile(fileName.c_str(), std::ofstream::binary);
    ImportanceSamplingFileHeader header(elevationCount, azimuthCount);

    // write header
    outFile.write(reinterpret_cast<char*>(&header), sizeof(header));
    size_t pdfTableSize = (elevationCount+1) * (azimuthCount+1);
    size_t cdfTableSize = elevationCount * azimuthCount;

    // writing binary data
    for(size_t i = 0; i<=elevationCount; i++)
    {
      shared_ptr<Lipis::LipisAngleData> precalc = angleData[i];
      outFile.write(reinterpret_cast<char*>(&precalc->OutgoingAngle), sizeof(number));
      outFile.write(reinterpret_cast<char*>(&precalc->PdfValues[0]), pdfTableSize*sizeof(number));
      outFile.write(reinterpret_cast<char*>(&precalc->CdfValues[0]), cdfTableSize*sizeof(number));
    }
  }

  bool LipisSerializer::Load(std::string materialSignature, 
    size_t elevationCount, 
    size_t azimuthCount, 
    std::vector<shared_ptr<Lipis::LipisAngleData>>& angleData)
  {
    try
    {
      std::string fileName = SignatureToFilename(materialSignature, ".isf");
      std::ifstream inFile(fileName.c_str(), std::ifstream::binary);
      size_t pdfTableSize = (elevationCount+1) * (azimuthCount+1);
      size_t cdfTableSize = elevationCount * azimuthCount;

      // read and check header
      ImportanceSamplingFileHeader header(elevationCount, azimuthCount);
      ImportanceSamplingFileHeader correctHeader(elevationCount, azimuthCount);
      inFile.read(reinterpret_cast<char*>(&header), sizeof(header));
      if (inFile.fail() || header != correctHeader) return false;

      for(size_t i = 0; i<=elevationCount; i++)
      {
        shared_ptr<Lipis::LipisAngleData> precalc(new Lipis::LipisAngleData);
        precalc->PdfValues.resize(pdfTableSize);
        precalc->CdfValues.resize(cdfTableSize);

        inFile.read(reinterpret_cast<char*>(&precalc->OutgoingAngle), sizeof(number));
        inFile.read(reinterpret_cast<char*>(&precalc->PdfValues[0]), pdfTableSize*sizeof(number));
        if (inFile.fail())
          throw 1;
        inFile.read(reinterpret_cast<char*>(&precalc->CdfValues[0]), cdfTableSize*sizeof(number));
        if (inFile.fail())
          throw 1;

        angleData.push_back(precalc);
      }

      return true;
    }
    catch(...)
    {
      std::cerr << "Failed to load importance sampling for " << materialSignature << std::endl;
      return false;
    }
  }

}