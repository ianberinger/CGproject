//
//  Tree.cpp
//  bRenderer_ios
//
//  Created by Ian Beringer on 5/3/16.
//
//

#include "Tree.h"


Tree::Tree(float x, float y, float z, float w, float h, float l, bool col):Entity(x, y, z, w, h, l, col){
    
}

void Tree::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
    ShaderPtr treeShader = r.getObjects()->getShader("tree");
    treeShader->setUniform("fogColor", fogColor);
    
    
    r.getModelRenderer()->drawModel("tree", "camera", modelMatrix*vmml::create_translation(getXYZ())*vmml::create_scaling(vmml::Vector3f(0.02f,0.02f,0.02f)), std::vector<std::string>({ }));
    
}

void Tree::update(Renderer &r, const vmml::Vector3f &collisionForce){
    //do something
    
}