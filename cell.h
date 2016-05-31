////////////////////////////////////////
// cell.h
////////////////////////////////////////

#ifndef CSE169_CELL_H
#define CSE169_CELL_H


#include <vector>
#include "vector3.h"
#include "particle.h"




////////////////////////////////////////////////////////////////////////////////

class Cell {
    
    

    
    Vector3 position;
    Vector3 velocity;
    float scalar;
    
    std::vector<Particle*> particles;

    
    float xMin, xMax, yMin, yMax, zMin, zMax;
    float Length;
    
    int xIndex, yIndex, zIndex;
    
    
public:
    
    Cell(float, float, float, float);
    void Draw();
    
    void addParticle(Particle*);
    
    Vector3 getPosition();
    Vector3 getVelocity();
    
    std::vector<Particle*>* getParticles();
    
    void printCell();
    
    void Update();
    
    
};



#endif







