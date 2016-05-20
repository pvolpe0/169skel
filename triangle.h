////////////////////////////////////////
// triangle.h
////////////////////////////////////////

#ifndef CSE169_TRIANGLE_H
#define CSE169_TRIANGLE_H

#include "core.h"
#include "vector3.h"
#include "vertex.h"
#include "matrix34.h"
#include "particle.h"

////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
    Triangle(Particle*, Particle*, Particle*);
    void Draw();
    void Update();

    void ComputeForce(float, float, Vector3);
    
private:

    Particle * a;
    Particle * b;
    Particle * c;
    
    // Variables


    Vector3 Normal;

    
};

////////////////////////////////////////////////////////////////////////////////



#endif
