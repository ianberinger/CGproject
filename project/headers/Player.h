//
//  Player.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#ifndef Player_h
#define Player_h

#include "Entity.h"
#include "Wheel.h"
#include "CollisionHandler.hpp"

class Player : public Entity{
public:
    Player();
    Player(float x, float y, float z, float w, float h, float l, bool col, Type type);
    
    virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r);
    void setRotAngle(float ang){rotAngle=ang;}
    float getRotAngle(){return rotAngle;}
    
    void setAddAngle(float ang){if(ang>0.3){addAngle=0.3;}else if(ang<-0.3){addAngle=-0.3;}else{addAngle=ang;}}
    float getAddAngle(){return addAngle;}
    
    void setComAngle(float ang){comAngle=ang;}
    float getComAngle(){return comAngle;}
    
    void setOffSetCam(float * off){offSetCam[0]=off[0];offSetCam[1]=off[1];offSetCam[2]=off[2];}
    float * getOffSetCam(){return offSetCam;}
    
    void setVelocity(float vel){velocity=vel;}
    float getVelocity(){return velocity;}
    
    void setAcceleration(float acc){acceleration=acc;}
    float getAcceleration(){return acceleration;}
    
    void setCollisionHandler(Collisionhandler *handler) {collisionHandler = handler;}
    
    void togglePause(){isPaused=!isPaused;}
    void toggleBirdsEye(){isBirdsEye=!isBirdsEye;}
    bool birdsEye(){return isBirdsEye;}
    
private:
    const float minSpeed=-0.2;
    const float maxSpeed=0.7;
    float rotAngle;
    float addAngle;
    float comAngle;
    float velocity;
    float acceleration;
    float offSetCam[3];
    bool isPaused = false;
    bool isBirdsEye = false;
    std::vector<std::shared_ptr<Wheel>> wheels;
    Collisionhandler *collisionHandler;
};

#endif /* Player_h */



