////////////////////////////////////////
// springhamper.cpp
////////////////////////////////////////

#include "springdamper.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////


SpringDamper::SpringDamper (Particle* a, Particle* b, float SprCnst, float DampFact, float RestLngth) {
    
    P1 = a;
    P2 = b;
    SpringConstant = SprCnst;
    DampingFactor = DampFact;
    RestLength = RestLngth;
}

void::SpringDamper::ComputeForce() {
    
    
    e = P2->GetPosition() - P1->GetPosition();
    length = e.Mag();
    e.Normalize();
    
    float v1, v2;
    v1 = e.Dot( P1->GetVelocity());
    v2 = e.Dot( P2->GetVelocity());
    
    
    float force1D = -SpringConstant * (RestLength - length) + -DampingFactor * (v1 - v2);
    
    Vector3 force3D = force1D * e;
    
    P1->ApplyForce(force3D);
    
    force3D.Negate();
    P2->ApplyForce(force3D);

}


void SpringDamper::Draw() {
    
    glColor3f(0.9, 0.9, 0.9);
    glLineWidth(1.0);
    
    
    glBegin(GL_LINES);
    
    glVertex3f(P1->GetPosition().x,
               P1->GetPosition().y,
               P1->GetPosition().z);
    glVertex3f(P2->GetPosition().x,
               P2->GetPosition().y,
               P2->GetPosition().z);
    
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////

















