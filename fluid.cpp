////////////////////////////////////////
// fluid.cpp
////////////////////////////////////////

#include "fluid.h"

////////////////////////////////////////////////////////////////////////////////

// mass
Fluid::Fluid(int quantity, float xMin, float yMin, float zMin, float length, float mass, float viscocity) {
    
    
    debug1 = 0;
    debug2 = quantity - 1;
    
    
    NumParticles = quantity;
    Mass = mass;
    Viscocity = viscocity;
    
    
    
    int cbroot = cbrt(NumParticles);
    this->length = length;
    
    this->xMin = xMin;
    this->xMax = xMin + length;
    
    this->yMin = yMin;
    this->yMax = yMin + length;
    
    this->zMin = zMin;
    this->zMax = zMin + length;

    int CellQuantity = 10000;
    
    field = new Field(CellQuantity, xMin, yMin, zMin, length);
    float x, y, z;
    
    int CellQuantCbRt = cbrt(CellQuantity);
    
    float SupportRadius = length / CellQuantCbRt;
    
    

    
    
    for (int i = 0; i < NumParticles; i++) {
       
    //  good
        x = RandomFloat(-.075, .075);
        y = RandomFloat(-0.3, -0.01);
        z = RandomFloat(-.075, .075);
  
  
       // x = RandomFloat(-0.005, 0.005);
       // y = RandomFloat(2.0, 2.0);
       // z = RandomFloat(-0.005, 0.005);
    
        particles.push_back(new Particle(mass, SupportRadius, Vector3(x,y,z), Viscocity));

    }



    

    particles[debug1]->setFixed(true);
   // particles[debug2]->setFixed(true);

}

float Fluid::RandomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
    
    
        return a + r;
    
}

void Fluid::Reset() {
    
    for (int i = 0; i < NumParticles; i++) {
        particles[i]->Reset();
    }
}



void Fluid::Draw() {
    
    for (int i = 0; i < NumParticles; i++) {
        
        particles[i]->Draw();
    }
    
    field->Draw();
 }

void Fluid::Update(float deltaTime) {
    
 

        particles[debug1]->setFixed(false);
    //particles[debug2]->setFixed(false);

    // clear cells
    field->Update();
    // clear all neighbors
    for (int i = 0; i < NumParticles; i++) {
        
        particles[i]->clearNeighbors();
    }
    
    
    // place particles into cells
    
    for (int i = 0; i < NumParticles; i++ ) {
        
        field->findCell( particles[i] );
    
    }
    

    
    // find neighbors
    for (int i = 0; i < NumParticles; i++) {
        
        field->findNeighbors( particles[i]);
    }
    
    
        particles[debug1]->setFixed(true);
       // particles[debug2]->setFixed(true);

    
    // calculate pressure
    for (int i = 0; i < NumParticles; i++) {
        
        
        particles[i]->CalculatePressure();
    }
    
    // calculate forces
    for (int i = 0; i < NumParticles; i++) {
        
        particles[i]->CalculateForces();
    }
    
    
    
    

    
    
    
    // Integrate
    
    for (int i = 0; i < NumParticles; i++) {
            
            particles[i]->Update(deltaTime);
            
        }
    
     //  particles[debug]->setFixed(false);
    

}












