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
    void incrementVelocity();
    void decrementVelocity();
    void togglePower();
    void setDirection(Vector3);
    
    Vector3 GetWind();
    
};



#endif







