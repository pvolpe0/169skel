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
    
    if (Position.y < -0.4) {
        
        Position.y = -0.4;
        Velocity.y = -0.1 * Velocity.y;
        Velocity.x = 0.95 * Velocity.x;
        Velocity.z = 0.95 * Velocity.z;
        
    }
    
    
}

void Particle::ApplyForce(Vector3 a) {
    
    Force += a;
}

void Particle::zeroNormal(){
    
    Normal.Zero();
}

void Particle::normalizeNormal() {
    
    Normal.Normalize();
}

void Particle::addVecToNorm(Vector3 x){
    
    Normal += x;
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

Vector3 Particle::GetNormal() {
    
    return Normal;
}


void Particle::SetFixed(bool a) {
    
    fixed = a;
    Force.Zero();
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
        glColor3f(0.0f,0.0f,1.0f); //green
    else
        glColor3f(1.0f,1.0f,1.0f); //white
    glPointSize(8.0f);//set point size to 10 pixels

    glBegin(GL_POINTS);
    glVertex3f(Position.x,
                   Position.y,
                   Position.z);
    
    glEnd();
    
    glLineWidth(2.0);
    glBegin(GL_LINES);
    
    glVertex3f(Position.x,
               Position.y,
               Position.z);
    glVertex3f(Position.x + Normal.x / 20,
               Position.y + Normal.y / 20,
               Position.z + Normal.z / 20);
    
    
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////

















