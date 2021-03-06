////////////////////////////////////////
// skin.h
////////////////////////////////////////

#ifndef CSE169_SKIN_H
#define CSE169_SKIN_H

#include "core.h"
#include "joint.h"
#include "vector3.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////

class Skin {
public:
    Skin();
    Skin(const char *);
    
    void Update();
    bool Load(const char*);
    void Draw();
    
private:
    // Constants
    Joint* root;
    
    // Variables
    Matrix34 WorldMtx;


////////////////////////////////////////////////////////////////////////////////


#endif
