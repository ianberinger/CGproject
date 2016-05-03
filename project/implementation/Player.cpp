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

Player::Player():Entity(0.0f, 0.0f, 0.0f, 1.5, 1, 2.5, true, Entity::Type::PLAYER){
    
    //wheels for the car
    std::shared_ptr<Wheel> w1( new Wheel(2.1,1.5,3.0,1,1,1,true, Entity::Type::WHEEL) );
    std::shared_ptr<Wheel> w2( new Wheel(-1.9,1.5,3.0,1,1,1,true, Entity::Type::WHEEL) );
    std::shared_ptr<Wheel> w3( new Wheel(2.1,1.5,-1.5,1,1,1,true, Entity::Type::WHEEL) );
    std::shared_ptr<Wheel> w4( new Wheel(-1.9,1.5,-1.5,1,1,1,true,Entity::Type::WHEEL) );
    
    wheels.push_back(w1);
    wheels.push_back(w2);
    wheels.push_back(w3);
    wheels.push_back(w4);
    
}

Player::Player(float x, float y, float z, float w, float h, float l, bool col, Type type):Entity(x, y, z, w, h, l, col, type){
    setVelocity(0);
    setAcceleration(0.2);
    
}

void Player::draw(Renderer &r, vmml::Matrix4f &modelMatrix){
    
    ShaderPtr guyShader = r.getObjects()->getShader("car");
    guyShader->setUniform("fogColor", this->fogColor);
    
    collisionHandler->applyGravity();
    
    vmml::Matrix4f transformationMatrix{modelMatrix};
    transformationMatrix *= vmml::create_translation(vmml::Vector3f(getX(),getY(),getZ()))*vmml::create_rotation(_collisionForce.y(), vmml::Vector3f::UNIT_X)*vmml::create_rotation(getAddAngle()+getComAngle(), vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(0.75f));
    
    for(auto e : wheels){
        e->draw(r, transformationMatrix);
        
    }
    
    r.getModelRenderer()->drawModel("car", "camera", transformationMatrix, std::vector<std::string>({ }));
    
}

void Player::update(Renderer &r, const vmml::Vector3f &collisionForce){
    _collisionForce = collisionForce;
    
    //Getting the inputs from the gyro sensor
    float roll = r.getInput()->getGyroscopeRoll(); // tilt
    float pitch = r.getInput()->getGyroscopePitch(); // left / right
    /*bRenderer::log("roll:" + std::to_string(roll));
     bRenderer::log("pitch:" + std::to_string(pitch));*/
    
    setVelocity(h.clip(getVelocity()+((roll+0.75)/20), minSpeed ,maxSpeed));
    
    setAddAngle(pitch);
    float velocityz= (pitch*4*M_PI_F)/180;
    
    for(auto e : wheels){
        e->update(r, collisionForce);
        
    }
    
    
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
    }
}

