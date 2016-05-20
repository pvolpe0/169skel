////////////////////////////////////////
// wind.h
////////////////////////////////////////

#ifndef CSE169_WIND_H
#define CSE169_WIND_H



#include "vector3.h"




////////////////////////////////////////////////////////////////////////////////

class Wind {
    
    
    Vector3 wind;
    bool power;
    float oldMag;
    Vector3 oldWind;
    
    
public:
    
    Wind();
    Wind(Vector3);
    void Draw();
    void incrementXVelocity();
    void decrementXVelocity();
    void incrementYVelocity();
    void decrementYVelocity();
    void incrementZVelocity();
    void decrementZVelocity();
    void zeroWind();
    void togglePower();
    void setDirection(Vector3);
    
    Vector3 GetWind();
    
};



#endif







