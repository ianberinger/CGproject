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
#include "Player.h"
#include "vmmlib/util.hpp"

class Collisionhandler {
public:
    enum Side {X, Z, NONE};

    Collisionhandler();
    bool testAABBOverlap(const Player &a, const Entity &b);
    void handleCollision(const Entity &a, Side side);
    vmml::Vector3f getCollisionForce();
private:
    Side getCollisionSide(float max_x, float min_x, float max_z, float min_z, const Entity &a, const Entity &b);
    vmml::Vector3f collisionForce;
};

#endif /* CollisionHandler_hpp */
