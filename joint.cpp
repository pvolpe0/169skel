////////////////////////////////////////
// joint.cpp
////////////////////////////////////////

#include "joint.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Joint::Joint() {
    // Initialize constant data
    WorldMtx.Identity();
    LocalMtx.Identity();
    offset.Set(0,0,0);
    boxmin.Set(-0.1,-0.1,-0.1);
    boxmax.Set(0.1,0.1,0.1);
    dofs.push_back(new DOF(0, -100000, 100000)); // x
    dofs.push_back(new DOF(0, -100000, 100000)); // y
    dofs.push_back(new DOF(0, -100000, 100000)); // z
    pose.Set(0,0,0);
 

    
}

////////////////////////////////////////////////////////////////////////////////

void Joint::Update( Matrix34 parent) {
    // Update (animate) any variable properties
    
    

    Matrix34 rotMtx, transMtx;
    
    LocalMtx.Identity();
    rotMtx.MakeRotateX(dofs[0]->GetValue());
    LocalMtx.Dot( rotMtx, LocalMtx);
    rotMtx.MakeRotateY(dofs[1]->GetValue());
    LocalMtx.Dot( rotMtx, LocalMtx);
    rotMtx.MakeRotateZ(dofs[2]->GetValue());
    LocalMtx.Dot( rotMtx, LocalMtx);
    
    transMtx.MakeTranslate(offset);

    LocalMtx.Dot(transMtx, LocalMtx);
    
    
    WorldMtx.Dot(parent, LocalMtx);
    
    
    
    for (int i = 0; i < children.size(); i++)
        children[i]->Update(WorldMtx);

}

////////////////////////////////////////////////////////////////////////////////

bool Joint::Load(Tokenizer token) {
    
    
    
    token.FindToken("{");
    
    while(1) {
        char temp[256];
        token.GetToken(temp);
        if (strcmp(temp, "offset") == 0) {
            offset.x = token.GetFloat();
            offset.y = token.GetFloat();
            offset.z = token.GetFloat();
        }
        else if (strcmp(temp, "boxmin") == 0) {
            boxmin.x = token.GetFloat();
            boxmin.y = token.GetFloat();
            boxmin.z = token.GetFloat();
        }
        else if (strcmp(temp, "boxmax") == 0) {
            boxmax.x = token.GetFloat();
            boxmax.y = token.GetFloat();
            boxmax.z = token.GetFloat();
        }
        else if (strcmp(temp, "rotxlimit") == 0) {
            rotXlimit.x = token.GetFloat();
            rotXlimit.y = token.GetFloat();
            
           // printf("current X Min,Max: %f, %f\n", dofs[0]->min, dofs[0]->max);
            
            dofs[0]->SetMinMax(rotXlimit.x, rotXlimit.y);
            //printf("dof set X Min,Max: %f, %f\n", dofs[0]->min, dofs[0]->max);

        }
        else if (strcmp(temp, "rotylimit") == 0) {
            rotYlimit.x = token.GetFloat();
            rotYlimit.y = token.GetFloat();
            
            //printf("current Y Min,Max: %f, %f\n", dofs[1]->min, dofs[1]->max);

            
            dofs[1]->SetMinMax(rotYlimit.x, rotYlimit.y);
            //printf("dof set Y Min,Max: %f, %f\n", dofs[1]->min, dofs[1]->max);


        }
        else if (strcmp(temp, "rotzlimit") == 0) {
            rotZlimit.x = token.GetFloat();
            rotZlimit.y = token.GetFloat();
            

            
            dofs[2]->SetMinMax(rotZlimit.x, rotZlimit.y);


        }
        else if (strcmp(temp, "pose") == 0) {
            pose.x = token.GetFloat();
            pose.y = token.GetFloat();
            pose.z = token.GetFloat();
            
            dofs[0]->SetValue(pose.x);
            dofs[1]->SetValue(pose.y);
            dofs[2]->SetValue(pose.z);
            



        }
        else if (strcmp(temp, "balljoint") == 0) {
            //std::cout << "Balljoint added";
            Joint *jnt = new Joint();
            jnt->Load(token);
            AddChild(jnt);
        }
        else if (strcmp(temp,"}") == 0) return true;
        else token.SkipLine(); // Unrecognized token
    }
    
}

std::vector<Joint *> Joint::AddJointToVector(std::vector<Joint *> vec) {
    vec.push_back(this);
    
    for (int i = 0; i < children.size(); i ++) {
        vec = children[i]->AddJointToVector(vec);
    }
    
    return vec;
}

////////////////////////////////////////////////////////////////////////////////

void Joint::Draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(WorldMtx);
    
    drawWireBox(boxmin.x, boxmin.y, boxmin.z, boxmax.x, boxmax.y, boxmax.z);
    
    for (int i = 0; i < children.size(); i++)
        children[i]->Draw();

}

Matrix34 Joint::GetWorldMatrix() {
    
    return WorldMtx;
}

void Joint::AddChild( Joint * child) {
    
    children.push_back(child);
    
}

////////////////////////////////////////////////////////////////////////////////
