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
    Load("/Users/pablo/Desktop/cse169/files/wasp.skel");
    
}

Skeleton::Skeleton(const char *file) {
    WorldMtx.Identity();
    
    
    char result[100];   // array to hold the result.
    char path[] = "/Users/pablo/Desktop/cse169/files/";
    

    
    strcpy(result,path); // copy string one into the result.
    strcat(result,file);
    Load(result);

    
}

void Skeleton::incrementDOFSelect() {
    
    DOFSelect++;
    
    
    if (DOFSelect > joints.size() * 3)
        DOFSelect = joints.size() * 3;
    printf("increment DOFSelect: %d\n", DOFSelect);

    
}

void Skeleton::decrementDOFSelect() {
    
    DOFSelect--;
    

    
    if (DOFSelect < 0)
        DOFSelect = 0;
    
    printf("decrement DOFSelect: %d\n", DOFSelect);

}

void Skeleton::incrementDOFValue(){
    
    int dof = DOFSelect % 3;
    int joint = DOFSelect / 3;
    
    joints[joint]->incrementDOF(dof);
    
}

void Skeleton::decrementDOFValue(){
    
    int dof = DOFSelect % 3;
    int joint = DOFSelect / 3;
    
    joints[joint]->decrementDOF(dof);
    
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
