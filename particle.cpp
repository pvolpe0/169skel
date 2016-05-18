////////////////////////////////////////
// particle.cpp
////////////////////////////////////////

#include "particle.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////


Particle::Particle (float m, Vector3 p) {
    
    Mass = m;
    Position = p;
    fixed = false;
}

void Particle::Update( float deltaTime) {
    
    if ( !fixed ) {
        // Compute acceleration (Newton’s second law)
        Acceleration = ( 1.0 / Mass ) * Force;
    
        // Compute new position & velocity
        Velocity += Acceleration * deltaTime;
        Position += Velocity * deltaTime;
    
        // Zero out Force vector
        Force.Zero();
    }
    
}

float Particle::GetMass() {
    
    return Mass;
}

Vector3 Particle::GetPosition() {
    
    return Position;
}

Vector3 Particle::GetVelocity(){
    
    return Velocity;
}

Vector3 Particle::GetMomentum(){
    
    return Momentum;
}

Vector3 Particle::GetAcceleration(){
    
    return Acceleration;
}


void Particle::SetFixed(bool a) {
    
    fixed = a;
}

void Particle::toggleFixed() {
    
    fixed = !fixed;
}

void Particle::incrementX() {
    
    if (fixed)
        Position.x += 0.05;
}

void Particle::decrementX() {
    
    if (fixed)
        Position.x -= 0.05;
}

void Particle::incrementY() {
    
    if (fixed)
        Position.y += 0.05;
}

void Particle::decrementY() {
    
    if (fixed)
        Position.y -= 0.05;
}

void Particle::incrementZ() {
    
    if (fixed)
        Position.z += 0.05;
}

void Particle::decrementZ() {
    
    if (fixed)
        Position.z -= 0.05;
}

void Particle::Draw() {
    
    if (fixed)
        glColor3f(0.0f,1.0f,0.0f); //green
    else
        glColor3f(1.0f,1.0f,1.0f); //white
    glPointSize(8.0f);//set point size to 10 pixels

    glBegin(GL_POINTS);
    glVertex3f(Position.x,
                   Position.y,
                   Position.z);
    
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////

















