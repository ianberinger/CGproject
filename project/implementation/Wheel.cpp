//
//  Wheel.cpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#include "Wheel.h"

Wheel::Wheel():Entity(0.0f, 0.0f, 0.0f, 1.5, 1, 2.5, true, Entity::Type::NOTCOLLIDABLE){
    
    
}


Wheel::Wheel(float x, float y, float z, float w, float h, float l, bool col, Type type):Entity(x, y, z, w, h, l, col, type){
  
    
}

 void Wheel::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
    ShaderPtr cubeShader = r.getObjects()->getShader("wheel");
    cubeShader->setUniform("fogColor", fogColor);


     
     r.getModelRenderer()->drawModel("wheel", "camera", modelMatrix*vmml::create_translation(getXYZ())*vmml::create_rotation(getRotAngle(),vmml::Vector3f::UNIT_Y)*vmml::create_rotation(getComAngle(),vmml::Vector3f::UNIT_X)*vmml::create_scaling(vmml::Vector3f(0.5f)), std::vector<std::string>({ }));


}

void Wheel::update(Renderer &r, const vmml::Vector3f &collisionForce){
    float roll = r.getInput()->getGyroscopeRoll();
    float pitch = r.getInput()->getGyroscopePitch();
    
    setRotAngle(pitch);
    setComAngle(roll);


}