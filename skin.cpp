////////////////////////////////////////
// skin.cpp
////////////////////////////////////////

#include "skin.h"
#include "token.h"
#include "skeleton.h"
#include <unistd.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////

Skin::Skin( Skeleton * skelptr, std::vector<Joint*> vec) {
    
    WorldMtx.Identity();
    skel = skelptr;
    joints = vec;
    Load("/Users/pablo/Desktop/wasp.skin");
    
}

Skin::Skin(Skeleton * skelptr, const char *file, std::vector<Joint *> vec) {
    WorldMtx.Identity();
    joints = vec;
    
    char path[] = "/Users/pablo/Desktop/";
    strcat( path,file);
    Load(path);
    
}

////////////////////////////////////////////////////////////////////////////////

void Skin::Update() {
    // Update (animate) any variable properties

    //for each joint, calculate M = W . B^-1
    std::vector<Matrix34> MMatrices;
    Matrix34 m;
    for (int i = 0; i < numJoints; i++) {
        m.Dot(skel->GetWorldMatrix(i), bindingInvMs[i]);
        MMatrices.push_back(m);
    }
    //loop through all vertices, compute blended positions
    
    for (int i = 0; i < numVerts; i++) {
        Vertex vtx;
        Vector3 blendPos;
        Vector3 blendNorm;
        std::vector<int> tmpIndex = vertices[i]->GetJointIndexVec();
        std::vector<float> tmpWeight = vertices[i]->GetWeightVec();
        for(int j = 0; j < tmpWeight.size(); j++) {
            Vector3 tmpBlendPos;
            Vector3 tmpBlendNorm;
            
            
            MMatrices[tmpIndex[j]].Transform(vertices[i]->GetPosition(), tmpBlendPos);
            MMatrices[tmpIndex[j]].Transform(vertices[i]->GetNormal(), tmpBlendNorm);
            blendPos = blendPos + tmpWeight[j] * tmpBlendPos;
            blendNorm = blendNorm + tmpWeight[j] * tmpBlendNorm;
            
        }
       
        vtx.SetPosition(blendPos.x, blendPos.y, blendPos.z);
        
        blendNorm = blendNorm.Normalize();
        vtx.SetNormal(blendNorm.x, blendNorm.y, blendNorm.z);
        
        blendVertices.push_back(vtx);
        
    }
    
    for (int i = 0; i < numTriangles; i++) {
        triangles[i]->SetVertices(blendVertices[triangles[i]->GetVertex(0)],
                                  blendVertices[triangles[i]->GetVertex(1)],
                                  blendVertices[triangles[i]->GetVertex(2)]);
    }
   
    
    
}


void Skin::setJointsVector(std::vector<Joint*> vec){
    
    
    joints = vec;
}
////////////////////////////////////////////////////////////////////////////////

bool Skin::Load(const char *file) {
    
    
    
    
    Tokenizer token;
    
    token.Open(file);
    
    bool done = false;
    
    
    
    
    while(!done) {
        char temp[256];
        token.GetToken(temp);
        if(strcmp(temp,"positions")==0) {
            numVerts = token.GetInt();
            token.GetToken(temp);
            for( int i = 0; i < numVerts; i++) {
                
                
                float x = token.GetFloat();
                float y = token.GetFloat();
                float z = token.GetFloat();
                
                vertices.push_back(new Vertex(x, y, z));
            }
        }
        else if (strcmp(temp,"normals")==0) {
            
            int tempr = token.GetInt();
            token.GetToken(temp);
            for (int i = 0; i < numVerts; i++) {
                
                float x = token.GetFloat();
                float y = token.GetFloat();
                float z = token.GetFloat();
                
                vertices[i]->SetNormal(x, y, z);
            }

        }
    
        else if (strcmp(temp,"skinweights")==0) {
            int tempr = token.GetInt();
            token.GetToken(temp);
            for (int i = 0; i < numVerts; i++) {
                
                int attachments = token.GetInt();
                for (int j = 0; j < attachments; j++) {
                    
                    int joint = token.GetInt();
                    float weight = token.GetFloat();
                    vertices[i]->AddJoint(joint, weight);
                }
            }
        }
        
        else if (strcmp(temp,"triangles")==0) {
            numTriangles = token.GetInt();
            token.GetToken(temp);
    
            for (int i = 0; i < numTriangles; i++) {
                
                int a = token.GetInt();
                int b = token.GetInt();
                int c = token.GetInt();
                
                triangles.push_back(new Triangle(a, b, c) );
                
            }
        }


    

        else if (strcmp(temp,"bindings")==0) {
            numJoints = token.GetInt();
            token.GetToken(temp);
            
            for (int i = 0; i < numJoints; i++) {
      
                token.GetToken(temp);
                token.GetToken(temp);
                float ax = token.GetFloat();
                float ay = token.GetFloat();
                float az = token.GetFloat();
                float bx = token.GetFloat();
                float by = token.GetFloat();
                float bz = token.GetFloat();
                float cx = token.GetFloat();
                float cy = token.GetFloat();
                float cz = token.GetFloat();
                float dx = token.GetFloat();
                float dy = token.GetFloat();
                float dz = token.GetFloat();
                
                Matrix34 binding(ax, bx, cx, dx,
                                 ay, by, cy, dy,
                                 az, bz, cz, dz );
                
                bindingMs.push_back(binding);
                
                Matrix34 bindingInv(ax, bx, cx, dx,
                                    ay, by, cy, dy,
                                    az, bz, cz, dz );
                
                bindingInv.Inverse();
                
                bindingInvMs.push_back(bindingInv);
                
                token.GetToken(temp);
                
            }

            done = true;
        } else {
            token.SkipLine();
        }
        
        
    }

    

    
    //Finish
    token.Close();
    return true;
}


////////////////////////////////////////////////////////////////////////////////

void Skin::Draw() {
    glLoadIdentity();
    
    for (int i = 0; i < numTriangles; i++) {
        
        triangles[i]->Draw();
    }
    
}

////////////////////////////////////////////////////////////////////////////////
