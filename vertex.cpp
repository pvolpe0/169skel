////////////////////////////////////////
// vertex.cpp
////////////////////////////////////////

#include "vertex.h"

////////////////////////////////////////////////////////////////////////////////

Vertex::Vertex(float x, float y, float z) {
    
    // Initialize constant data
    value.Set(x, y, z);

    
}

////////////////////////////////////////////////////////////////////////////////

void Vertex::SetValue( float x, float y, float z ) {
    
    value.Set(x, y, z);

}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vertex::GetVector() {
    
    return value;
}

////////////////////////////////////////////////////////////////////////////////
