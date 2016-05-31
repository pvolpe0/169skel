////////////////////////////////////////
// fluid.cpp
////////////////////////////////////////

#include "fluid.h"

////////////////////////////////////////////////////////////////////////////////

// mass
Fluid::Fluid(int quantity, float xMin, float yMin, float zMin, float length) {
    
    NumParticles = quantity;
    int cbroot = cbrt(NumParticles);
    float mass = 1.0;
    this->length = length;
    
    this->xMin = xMin;
    this->xMax = xMin + length;
    
    this->yMin = yMin;
    this->yMax = yMin + length;
    
    this->zMin = zMin;
    this->zMax = zMin + length;
    
    field = new Field(1000, xMin, yMin, zMin, length);
    float x, y, z;

    
    
    for (int i = 0; i < NumParticles; i++) {
        
        x = RandomFloat(-1, 1);
        y = RandomFloat(2.0, 3);
        z = RandomFloat(-1, 1);
        
        particles.push_back(new Particle(mass, Vector3(x,y,z)));

    }
    
    
    particles[0]->setFixed(true);
}
    
float Fluid::RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
    
    
        return a + r;
    
}



void Fluid::Draw() {
    
    for (int i = 0; i < NumParticles; i++) {
        
        particles[i]->Draw();
    }
    
    field->Draw();
 }

void Fluid::Update(float deltaTime) {
    
    
    // clear all neighbors
    for (int i = 0; i < NumParticles; i++) {
        
        particles[i]->clearNeighbors();
    }
    
    // clear cells
    field->Update();
    
    // place particles into cells
    
    for (int i = 0; i < NumParticles; i++ ) {
        
        field->findCell( particles[i] );
    
    }
    
    particles[0]->printCell();
    
    // find neighbors
    for (int i = 0; i < NumParticles; i++) {
        
        field->findNeighbors( particles[i]);
    }
    
    // Compute forces
    
    
    
    // Apply Gravity to each particle
    Vector3 gravity(0,-9.8,0);
    
    for (int i = 0; i < NumParticles; i++) {

            
            Vector3 force = gravity * particles[i]->GetMass(); // f=mg
            particles[i]->ApplyForce(force);
            particles[i]->zeroNormal();
            
    
    }
    
    

    
    
    
    // Integrate
    
    for (int i = 0; i < NumParticles; i++) {
            
            particles[i]->Update(deltaTime);
            
        }
    

}












