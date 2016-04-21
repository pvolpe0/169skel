////////////////////////////////////////
// vertex.h
////////////////////////////////////////

#ifndef CSE169_VERTEX_H
#define CSE169_VERTEX_H

#include <vector>
#include "core.h"
#include "vector3.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////

class Vertex {
public:
    Vertex();
    Vertex(float, float, float, float, float, float);
    Vertex(float, float, float);
    
    void SetPosition(float, float, float);
    void SetNormal(float, float, float);
    void AddJoint(int, float);
    Vector3 GetPosition();
    Vector3 GetNormal();
    std::vector<int> GetJointIndexVec();
    std::vector<float> GetWeightVec();

private:
    // Constants
    Vector3 position;
    Vector3 normal;
    
    int numOfAttach;
    std::vector<int> jointIndex;
    std::vector<float> weights;

    
    
    Matrix34 WorldMtx;
};

////////////////////////////////////////////////////////////////////////////////



#endif
