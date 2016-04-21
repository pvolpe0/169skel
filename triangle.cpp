////////////////////////////////////////
// triangle.cpp
////////////////////////////////////////

#include "triangle.h"

////////////////////////////////////////////////////////////////////////////////

Triangle::Triangle(int a, int b, int c) {
    
    // Initialize constant data
    index[0] = a;
    index[1] = b;
    index[2] = c;
    
    
}

int Triangle::GetVertex(int i) {
    
    return index[i];
}

void Triangle::SetVertices(Vertex a, Vertex b, Vertex c) {
    
    vertices[0] = a;
    vertices[1] = b;
    vertices[2] = c;
}

void Triangle::Draw() {
    
    /*float mat[4];
    
    mat[0] = 0.0215;
    mat[1] = 0.1745;
    mat[2] = 0.0215;
    mat[3] = 1.0;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
    
    mat[0] = 0.97568;
    mat[1] = 0.11424;
    mat[2] = 0.97568;
    
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
    
    mat[0] = 1;
    mat[1] = 1;
    mat[2] = 1;
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
    
    glMaterialf(GL_FRONT, GL_SHININESS, 0.6 * 128.0);*/
    
    glBegin(GL_TRIANGLES);
    
    glNormal3f(vertices[0].GetNormal().x,
               vertices[0].GetNormal().y,
               vertices[0].GetNormal().z );
    glVertex3f(vertices[0].GetPosition().x,
               vertices[0].GetPosition().y,
               vertices[0].GetPosition().z );

    glNormal3f(vertices[1].GetNormal().x,
               vertices[1].GetNormal().y,
               vertices[1].GetNormal().z );
    glVertex3f(vertices[1].GetPosition().x,
               vertices[1].GetPosition().y,
               vertices[1].GetPosition().z );

    glNormal3f(vertices[2].GetNormal().x,
               vertices[2].GetNormal().y,
               vertices[2].GetNormal().z );
    glVertex3f(vertices[2].GetPosition().x,
               vertices[2].GetPosition().y,
               vertices[2].GetPosition().z );

    glEnd();
}




////////////////////////////////////////////////////////////////////////////////

