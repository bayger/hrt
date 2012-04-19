/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-2010 H-RT Team.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#ifndef _DETERMINISTICINTEGRATOR_H
#define	_DETERMINISTICINTEGRATOR_H

#include "../LightIntegrator.h"

namespace Hrt
{
    
    class DeterministicIntegrator : public LightIntegrator
    {
    public:
        DeterministicIntegrator(unsigned int level = 3) : m_maxLevel(level) {}
        
        virtual void CalculateLight(const Ray& ray, Scene& scene, RayLight& result,
                unsigned level, RenderingContext& rc) const;

        virtual int GetMaxLevels() const { return m_maxLevel; }
        
        AUTO_PROPERTY(unsigned, m_maxLevel, MaxLevel);
        
    private:
        unsigned m_maxLevel;
    };
    
}

#endif	/* _DETERMINISTICINTEGRATOR_H */

