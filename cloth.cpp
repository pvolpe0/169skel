////////////////////////////////////////
// cloth.cpp
////////////////////////////////////////

#include "cloth.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

// mass
Cloth::Cloth(int width, int height, float mass) {
    
    Width = width;
    Height = height;
    Mass = mass;
    
    editMode = false;
    selectR = 0;
    selectC = 0;
    
    NumParticles = Width * Height;
    NumSpringDampers = 0;
    NumTriangles = 0;
    

    float sideLength = sqrt(NumParticles);
    
    float increment = 1 / sideLength;
    
    float start = -0.5;
    
    SDRestLength = increment;
    SDSpringConstant = 900.0;
    SDDampingFactor = 20.0;
    
    float x;
    float y = start;
    for (int row = 0; row < Height ; row++) {
        
        x = start;
        std::vector<Particle*> rowVec;
        for (int col = 0; col < Width; col++) {
            
            rowVec.push_back(new Particle(Mass, Vector3(x, y, 0)));
            x += increment;
            
        }
        particles.push_back(rowVec);
        y+= increment;
        
        
    }
    
    for (int i = 0; i < Width; i++) {
        
        particles[Height - 1][i]->SetFixed(true);
    }
    
    
    
    particles[0][0]->SetFixed(true);
    particles[0][Width - 1]->SetFixed(true);

    
    
    for (int row = 0; row < Height; row++) {
        for (int col = 0; col < Width; col++) {
  
            bool up = row - 1 >= 0;
            bool down = row + 1 < Height;
            bool left = col - 1 >= 0;
            bool right = col + 1 < Width;
            
            // instantiate triangles
            if (down && right) {
                
                triangles.push_back(new Triangle( particles[row][col],
                                                  particles[row+1][col],
                                                  particles[row][col+1] ) );
                NumTriangles++;
            }
            
            if (up && left) {
                triangles.push_back(new Triangle( particles[row][col],
                                                 particles[row-1][col],
                                                 particles[row][col-1] ) );
                NumTriangles++;
            }
            
            
            // instantiate springdampers

            if (right) {
                
                springdampers.push_back(new SpringDamper( particles[row][col],
                                                          particles[row][col + 1],
                                                          SDSpringConstant,
                                                          SDDampingFactor,
                                                          SDRestLength) );
                NumSpringDampers++;
                
            }

            // check bottom neightbor
            if (down) {
                
                springdampers.push_back(new SpringDamper( particles[row][col],
                                                         particles[row + 1][col],
                                                         SDSpringConstant,
                                                         SDDampingFactor,
                                                         SDRestLength) );
                NumSpringDampers++;
                
                // check bottom left neightbor
                if (left) {
                    
                    springdampers.push_back(new SpringDamper( particles[row][col],
                                                             particles[row + 1][col - 1],
                                                             SDSpringConstant,
                                                             SDDampingFactor,
                                                             1.41 * SDRestLength) );
                    NumSpringDampers++;
                }
                
                // check bottom right neightbor
                if (right) {
                    
                    springdampers.push_back(new SpringDamper( particles[row][col],
                                                             particles[row + 1][col + 1],
                                                             SDSpringConstant,
                                                             SDDampingFactor,
                                                             1.41 * SDRestLength) );
                    NumSpringDampers++;
                }
            }
            

            
        }
    }
    
    
}

void Cloth::SetWind(Wind* windObject) {
    
    wind = windObject;
}

void Cloth::toggleSelector() {
    
    editMode = !editMode;
}

void Cloth::incrementSelector() {
    
    if ( ((selectR != Height - 1) || (selectC != Width - 1))) {
        
        if (selectC != Width - 1) {
            selectC++;
        }
        else {
            selectR++;
            selectC = 0;
        }
    }
}
void Cloth::decrementSelector() {
    
    if (selectC != 0 || selectR != 0) {
        
        if ( selectC != 0) {
            selectC--;
        }
        else {
            selectR--;
            selectC = Width - 1;
        }
    }
}

void Cloth::decrementX() {
    particles[selectR][selectC]->decrementX();
}
void Cloth::incrementX() {
    particles[selectR][selectC]->incrementX();
}
void Cloth::decrementY() {
    particles[selectR][selectC]->decrementY();
}
void Cloth::incrementY() {
    particles[selectR][selectC]->incrementY();
}
void Cloth::decrementZ() {
    particles[selectR][selectC]->decrementZ();
}
void Cloth::incrementZ() {
    particles[selectR][selectC]->incrementZ();
}

void Cloth::toggleFixed() {
    
    particles[selectR][selectC]->toggleFixed();
}



void Cloth::Update(float deltaTime) {
    
    // Compute forces
    
    // Apply Gravity to each particle
    Vector3 gravity(0,-9.8,0);
    
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            
            Vector3 force = gravity * particles[i][j]->GetMass(); // f=mg
            particles[i][j]->ApplyForce(force);
            
        }
    }

    
    // Compute and apply forces to each spring-damper
    
    for (int i = 0; i < NumSpringDampers; i++ ) {
        
        springdampers[i]->ComputeForce();
    }
    
    
    
    
    // compute and apply aerodynamic forces to each triangle
    
    for (int i = 0; i < NumTriangles; i++) {
        
        triangles[i]->ComputeForce(1.0, 1.0, wind->GetWind());
    }
    
    
    
    
    
    
    // Integrate
    
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            
            particles[i][j]->Update(deltaTime);
            
        }
    }
}

void Cloth::Draw() {
    
    
   /* for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            
            particles[i][j]->Draw();
            
        }
    }
    */
   /* for (int i = 0; i < NumSpringDampers; i++) {
        
        springdampers[i]->Draw();
    }
    */
    
    if (editMode) {
        
        particles[selectR][selectC]->Draw();
    }
        
    for (int i = 0; i < NumTriangles; i++) {
        
        triangles[i]->Draw();
    }
}














