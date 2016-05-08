////////////////////////////////////////
// vertex.cpp
////////////////////////////////////////

#include "vertex.h"

////////////////////////////////////////////////////////////////////////////////

Vertex::Vertex() {
    
    // Initialize constant data
    position.Set(0, 0, 0);
    normal.Set(0, 0, 0);
}

Vertex::Vertex(float px, float py, float pz, float nx, float ny, float nz) {
    
    // Initialize constant data
    position.Set(px, py, pz);
    normal.Set(nx, ny, nz);
    

    
}

Vertex::Vertex(float px, float py, float pz) {
    
    // Initialize constant data
    position.Set(px, py, pz);
    normal.Set(0, 0, 0);
    
    
    
}

/////////////////////////////////////////////////////////////////////////////////

void Vertex::SetPosition( float x, float y, float z ) {
    
    position.Set(x, y, z);

}

void Vertex::SetNormal( float x, float y, float z ) {
    
    normal.Set(x, y, z);
    
}

void Vertex::AddJoint( int index, float weight ) {
    
    jointIndex.push_back(index);
    weights.push_back(weight);
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Vertex::GetPosition() {
    
    return position;
}

Vector3 Vertex::GetNormal() {
    
    return normal;
}

std::vector<int> Vertex::GetJointIndexVec() {
    
    return jointIndex;
}

std::vector<float> Vertex::GetWeightVec() {
    
    return weights;
}
////////////////////////////////////////////////////////////////////////////////

