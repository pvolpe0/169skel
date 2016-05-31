////////////////////////////////////////
// fluid.h
////////////////////////////////////////

#ifndef CSE169_FLUID_H
#define CSE169_FLUID_H

#include "core.h"
#include "vector3.h"
#include "particle.h"
#include "field.h"
#include <iostream>
#include <vector>




////////////////////////////////////////////////////////////////////////////////

class Fluid {
    
    
    float Mass;
    Field * field;
    
    // Particles
    int NumParticles;
    std::vector<Particle*> particles;
    
    float xMin, xMax, yMin, yMax, zMin, zMax;
    float length;
    
    
    float RandomFloat(float, float);
    

    
    
public:
    
    
    Fluid(int, float, float, float, float);


    void Update(float);
    void Draw();

};



#endif







