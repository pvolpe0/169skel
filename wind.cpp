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

void Wind::Draw() {
    
    glLineWidth(5.0);
    
    
    glBegin(GL_LINES);
    
    glVertex3f(0,
               1,
               0);
    
    glVertex3f(0 + wind.x / 300,
               1 + wind.y / 300,
               0 + wind.z / 300);
    
    glEnd();
    
    glBegin(GL_POINTS);
    
    
    glPointSize(2.0f);
    glColor3f(0, 1, 0);
    glVertex3f(0 + wind.x / 300,
               1 + wind.y / 300,
               0 + wind.z / 300);
    
    glPointSize(15.0f);
    glColor3f(1, 0, 0);
    glVertex3f(0,
               1,
               0);
    
    

    
    glEnd();
}

void Wind::incrementXVelocity() {
    
    if (power) {
        wind += Vector3(10.0, 0.0, 0.0);
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::decrementXVelocity() {
    
    if (power) {
        wind -= Vector3(10.0, 0.0, 0.0);
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::incrementYVelocity() {
    
    if (power) {
        wind += Vector3(0.0, 10.0, 0.0);
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::decrementYVelocity() {
    
    if (power) {
        wind -= Vector3(0.0, 10.0, 0.0);
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::incrementZVelocity() {
    
    if (power) {
        wind += Vector3(0.0, 0.0, 10.0);
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::decrementZVelocity() {
    
    if (power) {
        wind -= Vector3(0.0, 0.0, 10.0);
    } else
        std::cout << "power not on" << std::endl;
}

void Wind::zeroWind() {
    
    if (power) {
        wind.Zero();
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




