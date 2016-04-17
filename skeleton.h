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
    
private:
    // Constants
    Joint* root;
    
    // Variables
    Matrix34 WorldMtx;
};

////////////////////////////////////////////////////////////////////////////////


#endif
