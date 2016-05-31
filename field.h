////////////////////////////////////////
// field.h
////////////////////////////////////////

#ifndef CSE169_FIELD_H
#define CSE169_FIELD_H


#include <vector>
#include "vector3.h"
#include "cell.h"
#include "particle.h"




////////////////////////////////////////////////////////////////////////////////

class Field {
    
    
    std::vector< std::vector< std::vector <Cell*> > > cells;


    int numOfCells;
    int cubeRoot;
    float PosJump;
    
    float xMin, xMax, yMin, yMax, zMin, zMax;
    float Length;
    
    void addParticleToCell(Particle*, int, int, int);
    
    
    
public:
    
    Field(int, float, float, float, float);
    void Draw();
    void Update();
    
    void findCell(Particle*);
    void findNeighbors(Particle*);

    
    Vector3 getPosition(int, int, int);
    Vector3 getVelocity(int, int, int);

    
};



#endif







