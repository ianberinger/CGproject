//
//  CollisionHandler.hpp
//  bRenderer_ios
//
//  Created by Lukas Vollenweider on 25/04/16.
//
//

#ifndef CollisionHandler_hpp
#define CollisionHandler_hpp

#include <iostream>
#include "Entity.h"
#include "vmmlib/util.hpp"

class Collisionhandler {
public:
    Collisionhandler();
    bool testAABBOverlap(const Entity &a, const Entity &b);
    void handleCollision(float max_x, float min_x, float max_z, float min_z, const Entity &a, const Entity &b);
    vmml::Vector3f getCollisionForce();
    void applyGravity();
private:
    vmml::Vector3f collisionForce;
    float _collisionAngle = 0.0;
    float _carHeight = 0.0;
    bool gravityFlag = false;
};

#endif /* CollisionHandler_hpp */
