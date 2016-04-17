////////////////////////////////////////
// skin.cpp
////////////////////////////////////////

#include "skin.h"
#include "token.h"
#include <unistd.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Skin::Skin() {
    
    WorldMtx.Identity();
    Load("test.skel");
    
}

Skin::Skin(const char *file) {
    WorldMtx.Identity();
    Load(file);
    
}

////////////////////////////////////////////////////////////////////////////////

void Skin::Update() {
    // Update (animate) any variable properties
    root->Update(WorldMtx);
    
}

////////////////////////////////////////////////////////////////////////////////

bool Skin::Load(const char *file) {
    
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

void Skin::Draw() {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(WorldMtx);
    
    root->Draw();
    
}

////////////////////////////////////////////////////////////////////////////////
