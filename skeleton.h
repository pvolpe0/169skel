////////////////////////////////////////
// skel.h
////////////////////////////////////////

#ifndef CSE169_SKELETON_H
#define CSE169_SKELETON_H

#include "core.h"
#include "joint.h"
#include "vector3.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////


class Skeleton {
public:
    Skeleton();
    Skeleton(const char *);
    
    void Update();
    bool Load(const char*);
    void Draw();
    
    void SetupJointVector();
    std::vector<Joint *> GetJointsVector();
    Matrix34 GetWorldMatrix(int);
    
    std::vector<Joint*> joints;
    
    void incrementDOFSelect();
    void decrementDOFSelect();
    void incrementDOFValue();
    void decrementDOFValue();
    
    
private:
    // Constants
    Joint* root;
    
    int DOFSelect;

    
    // Variables
    Matrix34 WorldMtx;
};

////////////////////////////////////////////////////////////////////////////////


#endif
