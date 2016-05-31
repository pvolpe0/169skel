////////////////////////////////////////
// particle.h
////////////////////////////////////////

#ifndef CSE169_PARTICLE_H
#define CSE169_PARTICLE_H


#include <vector>
#include "core.h"
#include "vector3.h"


////////////////////////////////////////////////////////////////////////////////

class Particle {
    

    float Mass;
    float Density;
    float Volume;
    float Pressure;
    
    Vector3 Position;
    Vector3 Acceleration;
    Vector3 Force;
    Vector3 Velocity;
    Vector3 Momentum;
    Vector3 Normal;
    
    int xCell, yCell, zCell;
    
    std::vector<Particle*> neighbors;
    
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
    
    void setFixed(bool);

    void Draw();
    void ApplyForce(Vector3);
    
    void toCell(int,int,int);
    void clearNeighbors();
    void addNeighbor(Particle*);
    void addNeighbor(std::vector<Particle*>*);
    
    Vector3 getCell();
    
    void printCell();
    
    
    
};



#endif


