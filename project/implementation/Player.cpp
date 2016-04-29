//
//  Player.cpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 24.04.16.
//
//

#include "Player.h"
#include "Helper.h"

Helper h;

Player::Player():Entity(0.0f, 0.0f, 0.0f, 1.5, 1, 2.5, true){
    
    
}

Player::Player(float x, float y, float z, float w, float h, float l, bool col):Entity(x, y, z, w, h, l, col){
    setVelocity(0);
    setAcceleration(0.2);
    
}

void Player::draw(Renderer &r, vmml::Matrix4f &modelMatrix){
    
    ShaderPtr guyShader = r.getObjects()->getShader("car");
    guyShader->setUniform("fogColor", this->fogColor);
    
    vmml::Matrix4f transformationMatrix{modelMatrix};
    transformationMatrix *= vmml::create_translation(vmml::Vector3f(getX(),getY(),getZ()))*vmml::create_rotation(getAddAngle()+getComAngle(), vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(0.75f));

    r.getModelRenderer()->drawModel("car", "camera", transformationMatrix, std::vector<std::string>({ }));
    
}

void Player::update(Renderer &r, const vmml::Vector3f &collisionForce){
    
    
    //Getting the inputs from the gyro sensor
    float roll = r.getInput()->getGyroscopeRoll(); // tilt
    float pitch = r.getInput()->getGyroscopePitch(); // left / right
    /*bRenderer::log("roll:" + std::to_string(roll));
    bRenderer::log("pitch:" + std::to_string(pitch));*/
    
    setVelocity(h.clip(getVelocity()+((roll+0.75)/20), minSpeed ,maxSpeed));
    
    setAddAngle(pitch);
    float velocityz= (pitch*4*M_PI_F)/180;
    
    //Setting the players new coordiantes and rotate him accordingly
    setComAngle(getComAngle()+velocityz);
    setRotAngle(velocityz);
    
    setX(getX()-getVelocity()*sinf(getComAngle()));
    setZ(getZ()-getVelocity()*cosf(getComAngle()));
    
    if (hasCollision()){
        bRenderer::log("COLLISION");
        setCollision(false);
        
        vmml::Vector3f newVelocity {getXYZ() + collisionForce};
        
        setX(newVelocity.x());
        setZ(newVelocity.z());
        
        if (getVelocity() < 0.0) {
            setX(getX()-getVelocity()*sinf(getComAngle()));
            setZ(getZ()-getVelocity()*cosf(getComAngle()));
        }
    }
}

