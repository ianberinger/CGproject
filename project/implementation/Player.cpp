//
//  Player.cpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 24.04.16.
//
//

#include "Player.h"

Player::Player():Entity(0.0f, 0.0f, 0.0f, 1, 2, 2, true){
    
    
}

Player::Player(float x, float y, float z, float w, float h, float l, bool col):Entity(x, y, z, w, h, l, col){
    setVelocity(0);
    setAcceleration(0.2);
    
}

void Player::draw(Renderer &r, vmml::Matrix4f modelMatrix){
    
    ShaderPtr guyShader = r.getObjects()->getShader("guy");
    guyShader->setUniform("fogColor", this->fogColor);
    
    
    vmml::Matrix4f transformationMatrix{modelMatrix};
    transformationMatrix *= vmml::create_translation(vmml::Vector3f(getX(),getY(),getZ()))*vmml::create_rotation(getComAngle(), vmml::Vector3f::UNIT_Y);

    r.getModelRenderer()->drawModel("guy", "camera", transformationMatrix, std::vector<std::string>({ }));
    
}

void Player::update(){
    //do something
    
}

