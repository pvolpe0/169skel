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
    Load("test.skel");
    
}

Skeleton::Skeleton(const char *file) {
    WorldMtx.Identity();
    Load(file);
    
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
    
    //Finish
    token->Close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void Skeleton::Draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(WorldMtx);
    
    root->Draw();

}

////////////////////////////////////////////////////////////////////////////////
