////////////////////////////////////////
// wind.cpp
////////////////////////////////////////

#include "wind.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////


Wind::Wind(Vector3 input) {
    
    wind = input;
    oldWind = wind;
    

    power = true;
}

Wind::Wind() {
    
    wind = Vector3(40.0, 40.0, 40.0);
    oldWind = wind;

    
    power = true;
}

void Wind::incrementVelocity() {
    
    if (power) {
        wind += Vector3(10.0, 10.0, 10.0);
        std::cout << "incrementing wind velocity to " << wind.Mag() << std::endl;
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::decrementVelocity() {
    
    if (power) {
        wind -= Vector3(10.0, 10.0, 10.0);
        std::cout << "decrementing wind velocity to " << wind.Mag() << std::endl;
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::togglePower() {
    
    if (power) {
        
        std::cout << "Powering off wind" << wind.Mag() << std::endl;
        oldWind = wind;
        wind.Zero();
        power = false;
    } else {
        
        std::cout << "Powering on wind" << std::endl;
        wind = oldWind;
        power = true;
    }
        
}

Vector3 Wind::GetWind() {
    
    return wind;
}



void Wind::setDirection(Vector3 newDirection) {
    
    oldMag = wind.Mag();
    
    wind = newDirection;
    wind.Normalize();
    
    wind *= oldMag;
    
}




