////////////////////////////////////////
// ground.cpp
////////////////////////////////////////

#include "ground.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Ground::Ground() {}


void Ground::Draw() {
    

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    
    // ground
    glNormal3f(0, 1, 0);
    glVertex3f(-5.0f, -0.401f, -5.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(-5.0f, -0.401f, 5.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(5.0f, -0.401f, 5.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(5.0f, -0.401f, -5.0f);
    
    
    
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////

















