////////////////////////////////////////
// triangle.cpp
////////////////////////////////////////

#include "triangle.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle(Particle* a, Particle* b , Particle* c) {
    
    // Initialize constant data
    this->a = a;
    this->b = b;
    this->c = c;
    
    
}

void Triangle::ComputeForce(float density, float drag, Vector3 airVelocity) {
    
    Vector3 Velocity = (a->GetVelocity() +
                b->GetVelocity() +
                c->GetVelocity() ) / 3;
    Velocity = Velocity - airVelocity;
    float VelocityMag = Velocity.Mag();
    
    Vector3 ab, ac;
    ab = b->GetPosition() - a->GetPosition();
    ac = c->GetPosition() - a->GetPosition();
    
    Normal.Cross(ab, ac);
    
    float area = Normal.Mag() / 2;
    Normal.Normalize();

    //std::cout << "\n\nold area: " << area << std::endl;
    
    area = area * (Velocity.Dot(Normal) / VelocityMag);
    

 /*  std::cout << "density: " << density << std::endl;
    std::cout << "Velocity Magnitude: " << VelocityMag << std::endl;
    std::cout << "Velocity Magnitude^2: " << VelocityMag * VelocityMag << std::endl;
    std::cout << "new Area: " << area << std::endl;
    std::cout << "Normal x y z: " << Normal.x << " " << Normal.y << " " << Normal.z << std::endl;
   */
    
    Vector3 force = - (density * VelocityMag * VelocityMag * area * Normal) / 2;
    force = force / 3;
    
  //  std::cout << "aeroforce: " << force.Mag() << std::endl;
    
    a->ApplyForce(force);
    b->ApplyForce(force);
    c->ApplyForce(force);
    
    
}


void Triangle::Draw() {
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    
    glVertex3f(a->GetPosition().x,
               a->GetPosition().y,
               a->GetPosition().z );

    glVertex3f(b->GetPosition().x,
               b->GetPosition().y,
               b->GetPosition().z );

    glVertex3f(c->GetPosition().x,
               c->GetPosition().y,
               c->GetPosition().z );

    glEnd();
}




////////////////////////////////////////////////////////////////////////////////

