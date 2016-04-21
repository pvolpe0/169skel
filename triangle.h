////////////////////////////////////////
// triangle.h
////////////////////////////////////////

#ifndef CSE169_TRIANGLE_H
#define CSE169_TRIANGLE_H

#include "core.h"
#include "vector3.h"
#include "vertex.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////

class Triangle {
public:
    Triangle(int, int, int);
    
    void SetVertices(Vertex, Vertex, Vertex);
    
    int GetVertex(int);
    void Draw();
    
private:
    // Constants
    int index[3];
    Vertex vertices[3];
    
    // Variables
    Matrix34 WorldMtx;
    
};

////////////////////////////////////////////////////////////////////////////////



#endif
