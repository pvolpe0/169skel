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
    float SupportRadius;
    float SmoothingRadius;
    float Viscocity;
    
    Vector3 InitialPosition;
    
    float MaxVelocity;
    
    Vector3 Position;
    Vector3 Acceleration;
    Vector3 Force;
    Vector3 Force_pressure;
    Vector3 Force_viscocity;
    Vector3 Force_other;
    Vector3 Force_sum;
    Vector3 Velocity;
    Vector3 Momentum;
    Vector3 Normal;
    
    int xCell, yCell, zCell;
    
    std::vector<Particle*> neighborsCells;
    std::vector<Particle*> neighbors;
    
    bool fixed;
    bool neighborTag;
    
    
public:
    
    Particle(float, float, Vector3, float);
    void Update(float);
    void zeroNormal();
    void normalizeNormal();
    void addVecToNorm(Vector3);
    float GetMass();
    float GetDensity();
    float GetPressure();
    Vector3 GetPosition();
    Vector3 GetVelocity();
    Vector3 GetAcceleration();
    Vector3 GetMomentum();
    Vector3 GetNormal();
    
    Vector3 Calculate_Q_PartialDerivate(Vector3);
    
    void Reset();

    void CalculateForces();
    void CalculatePressure();
    void CalculatePressureForce();
    void CalculateViscosityForce();
    void CalculateOtherForce();
    
    float F_function(float);
    float Fprime_function(float);
    
    void setFixed(bool);
    void setNeighborTag(bool);

    void Draw();
    void ApplyForce(Vector3);
    
    void toCell(int,int,int);
    void clearNeighbors();
    void addNeighbor(Particle*);
    void addNeighbor(std::vector<Particle*>*);
    void filterNeighbors();
    
    Vector3 getCell();
    
    void printCell();
    
    
    
};



#endif


