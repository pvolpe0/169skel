////////////////////////////////////////
// skin.h
////////////////////////////////////////

#ifndef CSE169_SKIN_H
#define CSE169_SKIN_H

#include "core.h"
#include "joint.h"
#include "vector3.h"
#include "vertex.h"
#include "matrix34.h"
#include "triangle.h"
#include "skeleton.h"

////////////////////////////////////////////////////////////////////////////////

class Skin {
public:
    Skin(Skeleton*,std::vector<Joint*> vec);
    Skin(Skeleton*, const char *, std::vector<Joint*> vec);
    
    void Update();
    bool Load(const char*);
    void Draw();
    void setJointsVector(std::vector<Joint*>);
    
private:
    
    int numVerts;
    int numTriangles;
    int numJoints;
    
    Skeleton * skel;
    
    // Constants
    std::vector<Vertex*> vertices;
    std::vector<Vertex> blendVertices;
    std::vector<Triangle*> triangles;
    std::vector<Matrix34> bindingMs;
    std::vector<Matrix34> bindingInvMs;
    std::vector<Joint *> joints;
    
    
    Matrix34 B, Bi;
    
    // Variables
    Matrix34 WorldMtx;

};
////////////////////////////////////////////////////////////////////////////////


#endif
