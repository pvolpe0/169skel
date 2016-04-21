////////////////////////////////////////
// skel.cpp
////////////////////////////////////////

#include "skeleton.h"
#include "token.h"
#include <unistd.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Skeleton::Skeleton() {
    
    WorldMtx.Identity();
    Load("wasp.skel");
    
}

Skeleton::Skeleton(const char *file) {
    WorldMtx.Identity();
    
    char path[] = "/Users/pablo/Desktop/";
    strcat( path,file);
    Load(path);

    
}

////////////////////////////////////////////////////////////////////////////////

void Skeleton::Update() {
    // Update (animate) any variable properties
    root->Update(WorldMtx);

}

////////////////////////////////////////////////////////////////////////////////

bool Skeleton::Load(const char *file) {
    
    WorldMtx.Identity();
    

    Tokenizer * token = new Tokenizer();
    
    token->Open(file);

    token->FindToken("balljoint");
    
    // Parse tree
    root = new Joint();
    root->Load(*token);
    SetupJointVector();
    
    //Finish
    token->Close();
    return true;
}

Matrix34 Skeleton::GetWorldMatrix(int i) {
    
    return joints[i]->GetWorldMatrix();
}

void Skeleton::SetupJointVector() {
    joints = root->AddJointToVector(joints);
}

std::vector<Joint *> Skeleton::GetJointsVector() {
    
    return joints;
}
////////////////////////////////////////////////////////////////////////////////

void Skeleton::Draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(WorldMtx);
    
    root->Draw();

}

////////////////////////////////////////////////////////////////////////////////
