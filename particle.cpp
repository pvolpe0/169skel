////////////////////////////////////////
// particle.cpp
////////////////////////////////////////

#include "particle.h"
#include <iostream>

#define F_COEF 0.4774648293

////////////////////////////////////////////////////////////////////////////////


Particle::Particle (float m, float supportR, Vector3 p, float visco) {
    
    Mass = m;
    SupportRadius = supportR;
    SmoothingRadius = SupportRadius / 2;
    //SmoothingRadius = SupportRadius;
    InitialPosition = p;
    Position = p;
    Viscocity = visco;
    
    MaxVelocity = 2 * 0.4 * 0.0238 / 0.1;
    
    Force_other = Mass * Vector3(0, -9.8, 0);
    
    xCell = yCell = zCell = -1;
    fixed = false;
    neighborTag = false;

}

void Particle::Reset() {
    
    Force.Zero();
    Position = InitialPosition;
}


void Particle::Update( float deltaTime) {
    


    
    
    
        // Compute acceleration (Newton’s second law)
        Acceleration = ( 1.0 / Mass ) * Force;
    
        // Compute new position & velocity
        Velocity += Acceleration * deltaTime;
    
        if (Velocity.Mag() > MaxVelocity) {
        
            Velocity.Normalize();
            Velocity *= 5 * MaxVelocity;
        }
    
        Position += Velocity * deltaTime;
    
        // Zero out Force vector
        Force.Zero();
    
    
    // repel field
    if (Position.y <= -0.5) {
        
      //  ApplyForce(200000000000 * Vector3(0, -0.5 + Position.y , 0));
    }
   
    
    
    // ground
    if (Position.y <= -0.99) {
        
        Position.y = -0.99;
        Velocity.y = -0.4 * Velocity.y;
        Velocity.x = 0.3 * Velocity.x;
        Velocity.z = 0.3 * Velocity.z;
        
    }
    
    // roof
    if (Position.y >= 0) {
        
        Position.y = 0;
        Velocity.y = -0.4 * Velocity.y;
        Velocity.x = 0.95 * Velocity.x;
        Velocity.z = 0.95 * Velocity.z;
        
    }
    
    if (Position.x <= -0.45) {
        
        Position.x = -0.45;
        Velocity.x = -0.4 * Velocity.x;
        Velocity.y = 0.95 * Velocity.y;
        Velocity.z = 0.95 * Velocity.z;
        
    }
    
    if (Position.x >= 0.45) {
        
        Position.x = 0.45;
        Velocity.x = -0.4 * Velocity.x;
        Velocity.y = 0.95 * Velocity.y;
        Velocity.z = 0.95 * Velocity.z;
        
    }
    
    if (Position.z <= -0.45) {
        
        Position.z = -0.45;
        Velocity.z = -0.4 * Velocity.z;
        Velocity.y = 0.95 * Velocity.y;
        Velocity.x = 0.95 * Velocity.x;
        
    }
    
    if (Position.z >= 0.45) {
        
        Position.z = 0.45;
        Velocity.z = -0.4 * Velocity.z;
        Velocity.y = 0.95 * Velocity.y;
        Velocity.x = 0.95 * Velocity.x;
        
    }
    
    
}

void Particle::CalculatePressure() {
    

    
    Density = 1;
    Pressure = 1;
    float restDensity = 1000;
    
    if (neighbors.empty() || Position.y > 0)
        return;

    float W_tot = 0;
    for (int i = 0; i < neighbors.size(); i++) {
        
        Particle * neighbor = neighbors[i];
        
        Vector3 diff = this->GetPosition() - neighbor->GetPosition();
        
        float q = diff.Mag() ;
        q = q / SmoothingRadius;
        
        //std::cout << q << std::endl;

        
        float coef = 1 / pow(SmoothingRadius, 3);
        
        float f = F_function(q);
        
        float W = coef * f;
        
        if (W > 0)
         //std::cout << W << std::endl;

        
        W_tot += W;

    
        Density += neighbor->GetMass() * W;
    }

   // std::cout << "\nDensity:" << Density << std::endl;
    
    
    Pressure = 1 * ( pow( Density / restDensity, 7) - 1);

  //  std::cout << "Pressure: " << Pressure << std::endl;


}

void Particle::CalculatePressureForce(){
    
    Force_pressure.Zero();
    
    float coef = -Mass / Pressure;
    
    // calculate del Pressure
    
    Vector3 accumulator;
    for (int i = 0; i < neighbors.size(); i++) {
        
        Particle * neighbor = neighbors[i];
        
        Vector3 diff = Position - neighbor->GetPosition();
        float q = diff.Mag() / SmoothingRadius;
        
        float n_mass = neighbor->GetMass();
        
        float mid = ((Pressure / pow(Density, 2)) + (neighbor->GetPressure() / pow(neighbor->GetDensity(), 2)));
        
        Vector3 Del_W = Fprime_function(q) * Calculate_Q_PartialDerivate(neighbor->GetPosition());
        
        accumulator += n_mass * mid * Del_W;
        
    }
    
    Vector3 del_Pressure = Density * accumulator;
    
    Force_pressure = coef * del_Pressure;
    
}

void Particle::CalculateForces() {
    

   // CalculateOtherForce();
    CalculatePressureForce();
    CalculateViscosityForce();
    
 //   Force_viscocity.Print();
    
    Force = 10000000 * Force_pressure +  Force_viscocity + Force_other;
    
    ApplyForce(Force);
    

}

void Particle::CalculateViscosityForce() {
    
    Force_viscocity.Zero();
    Vector3 accumulator;
    
    for (int i = 0; i < neighbors.size(); i++) {
        
        Particle * neighbor = neighbors[i];
        
        float volume = neighbor->GetMass() / neighbor->GetDensity();
        
        Vector3 mid = Velocity - neighbor->GetVelocity();
        
        Vector3 PosDiff = Position - neighbor->GetPosition();
        float q = PosDiff.Mag() / SmoothingRadius;
        
        Vector3 Del_W = Fprime_function(q) * Calculate_Q_PartialDerivate(neighbor->GetPosition());

        
        float numerator = PosDiff.Dot(Del_W);
        float denominator = PosDiff.Dot(PosDiff) + 0.01 * pow(SmoothingRadius, 2);
    
        float right = numerator / denominator;
        
        accumulator += volume * mid * right;
        
    }
    
    
    Vector3 Laplacian_velocity = 2 * accumulator;
    
    Force_viscocity = Mass * Viscocity * Laplacian_velocity;
}

void Particle::CalculateOtherForce() {
    
    
}

float Particle::F_function(float q) {
    
    float f;
    
    
    // f(q)
    if (q >= 0 && q < 1) {
        
        float powr1 = pow(q,2);
        float powr2 = pow(q,3);
        
        float term1 = (float) 2 / 3;
        float term2 = powr1;
        float term3 = powr2 / 2;
        
        f = term1 - term2 + term3;
        
    } else if (q <= 2) {
        
        float powr = pow(2 - q, 3);
        
        f = powr / 6;
        
    } else {
        f = 0;
    }

    
    f *= F_COEF;
    
    return f;
    
}

float Particle::Fprime_function(float q) {
    
    float f_prime;
    
    // f(q)
    if (q >= 0 && q < 1) {
        
        float powr1 = pow(q,2);
        
        float term1 = (float) (3 / 2) * powr1;
        float term2 = 2 * q;

        
        f_prime = term1 - term2;
        
    } else if (q <= 2) {
        
        float powr = pow(2 - q, 2);
        
        f_prime = -powr / 2;
        
    } else {
        f_prime = 0;
    }
    
    f_prime *= F_COEF;
    
    return f_prime;
}

Vector3 Particle::Calculate_Q_PartialDerivate(Vector3 j) {
    
    Vector3 i = this->GetPosition();
    
    float diff_x = i.x - j.x;
    float diff_y = i.y - j.y;
    float diff_z = i.z - j.z;
    
    float denominator = 1 / sqrt( pow( diff_x, 2) + pow( diff_y, 2) + pow( diff_z, 2) );
    
    return denominator * Vector3(diff_x, diff_y, diff_z);
}

void Particle::toCell(int x, int y, int z) {
    
    xCell = x;
    yCell = y;
    zCell = z;
}

void Particle::setFixed(bool v ) {
    
    fixed = v;
    
    if (fixed) {
        for (int i = 0; i < neighbors.size(); i++ ){
        
            neighbors[i]->setNeighborTag(true);
        }
    } else {
        
        for (int i = 0; i < neighbors.size(); i++ ){
            
            neighbors[i]->setNeighborTag(false);
        }
    }
}

void Particle::setNeighborTag(bool v ) {
    
    neighborTag = v;
}

Vector3 Particle::getCell() {
    
    return Vector3(xCell, yCell, zCell);
}

void Particle::clearNeighbors() {
    
    neighborsCells.clear();
    neighbors.clear();
}

void Particle::addNeighbor(Particle * particle) {
    
    neighbors.push_back(particle);
}

void Particle::filterNeighbors() {
    
    for (int i = 0; i < neighborsCells.size(); i++) {
        
        Particle * potentialNeighbor = neighborsCells[i];
        
        if (potentialNeighbor == this)
            continue;
        
        float distance = Position.Dist2(potentialNeighbor->GetPosition());
        
        if (distance < SupportRadius) {
            
            neighbors.push_back(potentialNeighbor);
        }
    }
    
    neighborsCells.clear();
    
}

void Particle::addNeighbor(std::vector<Particle*>* particles) {
    
    if (!particles->empty())
        neighborsCells.insert(neighborsCells.end(), particles->begin(), particles->end());
    
    // remove this

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

float Particle::GetDensity() {
    
    return Density;
}

float Particle::GetPressure() {
    
    return Pressure;
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



    glPointSize(8.0f);//set point size to 10 pixels

    glBegin(GL_POINTS);

    
    if (fixed) {
        
        glColor3f(0,1,0);
    } else if (neighborTag){
        
        glColor3f(0, 0, 1); //blue
    }else {
        
        glColor3f(144.0f/ 255,195.0f/ 255,212.0f/ 255); //white
    }
    
    glNormal3f(0,1,0);
    
    glVertex3f(Position.x,
               Position.y,
               Position.z);
    
    glEnd();
    

}

////////////////////////////////////////////////////////////////////////////////

















