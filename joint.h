////////////////////////////////////////
// joint.h
////////////////////////////////////////

#ifndef CSE169_JOINT_H
#define CSE169_JOINT_H

#include <vector>
#include "core.h"
#include "token.h"
#include "DOF.h"
#include "vector3.h"
#include "matrix34.h"

////////////////////////////////////////////////////////////////////////////////

class Joint {
public:
    Joint();
    
    void Update(Matrix34);
    void Draw();
    bool Load(Tokenizer);
    void AddChild(Joint*);
    std::vector<Joint *> AddJointToVector(std::vector<Joint *>);
    Matrix34 GetWorldMatrix();
    
private:
    // Constants
    Vector3 offset, boxmin, boxmax, pose;
    Vector3 rotXlimit, rotYlimit, rotZlimit;
    char name[256];
    
    
    std::vector<DOF*> dofs;
    std::vector<Joint*> children;
    //std::vector<Joint*> sibling;
    //Joint* parent;
    
    

    
    
    // Variables
    Matrix34 WorldMtx;
    Matrix34 LocalMtx;
};

////////////////////////////////////////////////////////////////////////////////


#endif
