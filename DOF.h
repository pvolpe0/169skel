////////////////////////////////////////
// dof.h
////////////////////////////////////////

#ifndef CSE169_DOF_H
#define CSE169_DOF_H

#include "core.h"
#include "vector3.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////

class DOF {
public:
    DOF(float, float, float);
    
    bool SetValue(float);
    float GetValue();
    void SetMinMax(float, float);
    float min, max;
    
    bool incrementValue();
    bool decrementValue();
    
private:
    // Constants
    float value;
};

////////////////////////////////////////////////////////////////////////////////



#endif
