////////////////////////////////////////
// springdamper.h
////////////////////////////////////////

#ifndef CSE169_SPRINGDAMPER_H
#define CSE169_SPRINGDAMPER_H

#include "core.h"
#include "vector3.h"
#include "particle.h"



////////////////////////////////////////////////////////////////////////////////



class SpringDamper {
    
    float SpringConstant, DampingFactor;
    float RestLength;
    Particle *P1,*P2;
    Vector3 e;
    float length;
    
public:
    
    SpringDamper(Particle*, Particle*, float, float, float);
    void ComputeForce();
    void Draw();
};


#endif



