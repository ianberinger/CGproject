//
//  Barrier.cpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#include "Barrier.h"




Barrier::Barrier(float x, float y, float z, float w, float h, float l, bool col, Type type):Entity(x, y, z, w, h, l, col, type){
  
    
}

 void Barrier::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
     ShaderPtr cubeShader = r.getObjects()->getShader("cube");
     cubeShader->setUniform("fogColor", fogColor);

     
     r.getModelRenderer()->drawModel("cube", "camera", modelMatrix*vmml::create_translation(getXYZ())*vmml::create_scaling(vmml::Vector3f(2.0f, 1.0f, 2.0f)), std::vector<std::string>({ }));

}

void Barrier::update(Renderer &r, const vmml::Vector3f &collisionForce){
//do something

}