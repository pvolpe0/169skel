////////////////////////////////////////
// field.cpp
////////////////////////////////////////

#include "field.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Field::Field( int quant, float xMin, float yMin, float zMin, float length) {
    
    numOfCells = quant;
    cubeRoot = cbrt(numOfCells);
    
    Length = length;
    
    this->xMin = xMin;
    this->xMax = xMin + length;
    
    this->yMin = yMin;
    this->yMax = yMin + length;
    
    this->zMin = zMin;
    this->zMax = zMin + length;
    
    float x, y, z;

    x = xMin;
    y = yMin;
    z = zMin;
    
    

    PosJump = length / cubeRoot;
    
    for (int i = 0; i < cubeRoot; i++ ) {
        std::vector<std::vector< Cell* > > yzCells;

        for (int j = 0; j < cubeRoot; j++) {
            
            std::vector<Cell*> zCells;


            for (int k = 0; k < cubeRoot; k++) {
                
                zCells.push_back( new Cell(x, y, z, PosJump) );
                
                z += PosJump;
            }
            z = zMin;
            
            yzCells.push_back(zCells);
            
            y += PosJump;
        }
        y = yMin;
        
        cells.push_back(yzCells);
        
        x += PosJump;
    }
    
    
    
    
    
}

Vector3 Field::getPosition(int x, int y, int z) {
    
    return cells[x][y][z]->getPosition();
}

Vector3 Field::getVelocity(int x, int y, int z) {
    
    return cells[x][y][z]->getVelocity();
}


void Field::findCell(Particle * particle) {
    
    Vector3 pos = particle->GetPosition();
    
    if (pos.y < 0 && pos.y > -1) {
    
        int xIndex = (pos.x + .5) * 10;
        int yIndex = (pos.y + 1) * 10;
        int zIndex = (pos.z + .5) * 10;
    
        addParticleToCell(particle, xIndex, yIndex, zIndex);
        
    }
}

void Field::findNeighbors(Particle* particle) {
    
    Vector3 cell = particle->getCell();
    
    if (cell.x == -1)
     //   return;
    
    if (cell.y == 0)
        std::cout << "";
    
    for (int z = cell.z - 1; z <= cell.z + 1; z++ ) {
        
        if (z < 0 || z > cubeRoot - 1)
            continue;
        for (int y = cell.y - 1; y <= cell.y + 1; y++) {
            
            if (y < 0 || y > cubeRoot - 1)
                continue;
            for (int x = cell.x - 1; x <= cell.x + 1; x++) {
                
                if (x < 0 || x > cubeRoot - 1)
                    continue;
             
                Cell * adjCell = cells[x][y][z];
                std::vector<Particle*> * neighbors = adjCell->getParticles();
                particle->addNeighbor(neighbors);
                
                
            }
        }
    }
    
    particle->filterNeighbors();
    
}

void Field::addParticleToCell(Particle * particle, int x, int y, int z) {
    
    particle->toCell(x,y,z);
    cells[x][y][z]->addParticle(particle);
}



void Field::Update() {
    
  //      cells[0][0][0]->printCell();
    for (int i = 0; i < cubeRoot; i++) {
        for (int j = 0; j < cubeRoot; j++) {
            for (int k = 0; k < cubeRoot; ++k) {
                
                cells[i][j][k]->Update();
            }
        }
    }
    
    
    

}

void Field::Draw() {
    
    glColor3f(1, 0,0); //white
    glPointSize(2.0f);//set point size to 10 pixels
    
        glBegin(GL_POINTS);
    
    for (int i = 0; i < cubeRoot; i++ ) {
        for (int j = 0; j < cubeRoot; j++) {
            for (int k = 0; k < cubeRoot; k++) {
                
                
                glVertex3f(cells[i][j][k]->getPosition().x,
                           cells[i][j][k]->getPosition().y,
                           cells[i][j][k]->getPosition().z);

            }
        }
    }
    
    


    
    glEnd();
}






////////////////////////////////////////////////////////////////////////////////

