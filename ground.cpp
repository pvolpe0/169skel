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
    glVertex3f(-5.0f, -1.01f, -5.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(-5.0f, -1.01f, 5.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(5.0f, -1.01f, 5.0f);
    
    glNormal3f(0, 1, 0);
    glVertex3f(5.0f, -1.01f, -5.0f);
    
    
    
    glEnd();
    
        glColor3f(0, 0, 0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    
    glVertex3f(-0.5f, -0.99f, -0.5f);
    glVertex3f(-0.5f, -0.99f, 0.5f);
    
    glVertex3f(-0.5f, -0.99f, -0.5f);
    glVertex3f(0.5f, -0.99f, -0.5f);

    
    glVertex3f(0.5f, -0.99f, 0.5f);
    glVertex3f(-0.5f, -0.99f, 0.5f);
    
    glVertex3f(0.5f, -0.99f, -0.5f);
    glVertex3f(0.5f, -0.99f, 0.5f);
    
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    
    glVertex3f(-0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    
    
    glVertex3f(0.5f, 0.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    
    glVertex3f(0.5f, 0.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    
    glVertex3f(-0.5f, -1.0f, 0.5f);
    glVertex3f(-0.5f, 0.0f, 0.5f);
    
    glVertex3f(-0.5f, -1.0f, -0.5f);
    glVertex3f(-0.5f, 0.0f, -0.5f);
    
    
    glVertex3f(0.5f, -1.0f, -0.5f);
    glVertex3f(0.5f, 0.0f, -0.5f);
    
    glVertex3f(0.5f, -1.0f, 0.5f);
    glVertex3f(0.5f, 0.0f, 0.5f);
    
    
    
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////

















