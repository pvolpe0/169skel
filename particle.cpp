////////////////////////////////////////
// particle.cpp
////////////////////////////////////////

#include "particle.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////


Particle::Particle (float m, Vector3 p) {
    
    Mass = m;
    Position = p;
    
    xCell = yCell = zCell = -1;
    fixed = false;
}


void Particle::Update( float deltaTime) {
    

        // Compute acceleration (Newton’s second law)
        Acceleration = ( 1.0 / Mass ) * Force;
    
        // Compute new position & velocity
        Velocity += Acceleration * deltaTime;
        Position += Velocity * deltaTime;
    
        // Zero out Force vector
        Force.Zero();
    
    if (Position.y <= -0.9) {
        
        Position.y = -0.9;
        Velocity.y = -0.7 * Velocity.y;
        Velocity.x = 0.95 * Velocity.x;
        Velocity.z = 0.95 * Velocity.z;
        
    }
    
    
}

void Particle::toCell(int x, int y, int z) {
    
    xCell = x;
    yCell = y;
    zCell = z;
}

void Particle::setFixed(bool v ) {
    
    fixed = v;
}

Vector3 Particle::getCell() {
    
    return Vector3(xCell, yCell, zCell);
}

void Particle::clearNeighbors() {
    
    neighbors.clear();
}

void Particle::addNeighbor(Particle * particle) {
    
    neighbors.push_back(particle);
}

void Particle::addNeighbor(std::vector<Particle*>* particles) {

    neighbors.insert(neighbors.end(), particles->begin(), particles->end());
}

void Particle::printCell() {
    
    std::cout << "in cell (" << xCell << ", " << yCell << ", " << zCell << ") ";
    std::cout << "neighbors quantity: " << neighbors.size() << std::endl;
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



void Particle::Draw() {


    glColor3f(233.0f/ 255,240.0f/ 255,36.0f/ 255); //white
    glPointSize(6.0f);//set point size to 10 pixels

    glBegin(GL_POINTS);

    
    if (fixed) {
        
        glColor3f(0,1,0);
        
        glVertex3f(Position.x,
                   Position.y,
                   Position.z);
    
        glColor3f(0, 0, 1); //blue
        for (int i = 0; i < neighbors.size(); i++) {
        
            glVertex3f(neighbors[i]->GetPosition().x,
                       neighbors[i]->GetPosition().y,
                       neighbors[i]->GetPosition().z);
        }
    } else {
        
        
        glVertex3f(Position.x,
                   Position.y,
                   Position.z);
    }
    
    glEnd();
    

}

////////////////////////////////////////////////////////////////////////////////

















