////////////////////////////////////////
// cloth.h
////////////////////////////////////////

#ifndef CSE169_CLOTH_H
#define CSE169_CLOTH_H

#include "core.h"
#include "wind.h"
#include "vector3.h"
#include "particle.h"
#include "triangle.h"
#include "springdamper.h"



////////////////////////////////////////////////////////////////////////////////

class Cloth {
    
    
    int Width;
    int Height;
    float Mass;
    
    // Particles
    int NumParticles;
     std::vector< std::vector<Particle*> > particles;
    
    // SpringDamper
    int NumSpringDampers;
    float SDRestLength;
    float SDSpringConstant;
    float SDDampingFactor;
    std::vector<SpringDamper*> springdampers;
    
    // Triangles
    int NumTriangles;
    std::vector<Triangle*> triangles;
    
    // Wind object
    Wind * wind;
    
    int selectR, selectC;
    
    bool editMode;
    bool fixedAll;
    
   

    
public:
    
    bool showSD, showP;
    
    Cloth(int, int, float);
    void toggleSelector();
    void toggleFixed();
    void incrementSelector();
    void decrementSelector();
    void SetWind(Wind*);
    void Update(float);
    void Draw();
    void decrementX();
    void incrementX();
    void decrementY();
    void incrementY();
    void decrementZ();
    void incrementZ();
    void fixAll();
};



#endif







