////////////////////////////////////////
// particle.h
////////////////////////////////////////

#ifndef CSE169_PARTICLE_H
#define CSE169_PARTICLE_H

#include "core.h"
#include "vector3.h"


////////////////////////////////////////////////////////////////////////////////

class Particle {
    

    float Mass;
    Vector3 Position;
    Vector3 Acceleration;
    Vector3 Force;
    Vector3 Velocity;
    Vector3 Momentum;
    Vector3 Normal;
    
    bool fixed;
    
    
public:
    
    Particle(float, Vector3);
    void Update(float);
    void zeroNormal();
    void normalizeNormal();
    void addVecToNorm(Vector3);
    float GetMass();
    Vector3 GetPosition();
    Vector3 GetVelocity();
    Vector3 GetAcceleration();
    Vector3 GetMomentum();
    Vector3 GetNormal();
    void SetFixed(bool);
    void toggleFixed();
    void incrementX();
    void decrementX();
    void incrementY();
    void decrementY();
    void incrementZ();
    void decrementZ();
    void Draw();
    void ApplyForce(Vector3);
    
    
    
};



#endif


