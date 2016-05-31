////////////////////////////////////////
// cell.cpp
////////////////////////////////////////

#include "cell.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Cell::Cell(float xMin, float yMin, float zMin, float length) {

    this->xMin = xMin;
    this->xMax = xMin + length;
    
    this->yMin = yMin;
    this->yMax = yMin + length;
    
    this->zMin = zMin;
    this->zMax = zMin + length;
    
    position = Vector3( xMin + length / 2,
                        yMin + length / 2,
                        zMin + length / 2) ;
    
    
    

    
}

Vector3 Cell::getPosition() {
    
    return position;
}

Vector3 Cell::getVelocity() {
    
    return velocity;
}

void Cell::addParticle(Particle * particle) {
    
    particles.push_back(particle);
}

void Cell::Update() {

    
    particles.clear();
    
}

void Cell::printCell() {
    
    std::cout << particles.size() << std::endl;
}

std::vector<Particle*>* Cell::getParticles() {
    
    std::vector<Particle*>* particlesPtr = &particles;
    
    return particlesPtr;
}



////////////////////////////////////////////////////////////////////////////////

















