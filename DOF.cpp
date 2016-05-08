////////////////////////////////////////
// dof.cpp
////////////////////////////////////////

#include "DOF.h"

////////////////////////////////////////////////////////////////////////////////

DOF::DOF(float value, float min, float max) {
   
    // Initialize constant data
    this->value = value;
    this->min = min;
    this->max = max;


}

////////////////////////////////////////////////////////////////////////////////

bool DOF::SetValue( float val ) {
    
    if (val > max) {
        value = max;
        return false;
    }
    else if (val < min) {
        value = min;
        return false;
    }
    else {
        value = val;
        return true;
    }
}

bool DOF::decrementValue() {
    
    
    return SetValue(GetValue() - 0.05);
}

bool DOF::incrementValue() {
    
    
    return SetValue(GetValue() + 0.05);
}

////////////////////////////////////////////////////////////////////////////////

float DOF::GetValue() {

    return value;
}

////////////////////////////////////////////////////////////////////////////////

void DOF::SetMinMax(float min, float max) {

    this->min = min;
    this->max = max;
}

////////////////////////////////////////////////////////////////////////////////
