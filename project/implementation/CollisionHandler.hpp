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
    enum Side {X, Z};

    Collisionhandler();
    bool testAABBOverlap(const Player &a, const Entity &b);
    void handleCollision(const Entity &a, Side side);
private:
};

#endif /* CollisionHandler_hpp */
