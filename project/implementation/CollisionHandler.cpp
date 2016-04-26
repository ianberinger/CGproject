//
//  CollisionHandler.cpp
//  bRenderer_ios
//
//  Created by Lukas Vollenweider on 25/04/16.
//
//

#include "CollisionHandler.hpp"

Collisionhandler::Collisionhandler() {
    
}

bool Collisionhandler::testAABBOverlap(const Player &a, const Entity &b) {
    
    float aMinX = a.getX() - a.getWidth() / 2 - a.getLength() / 2;
    float aMaxX = a.getX() + a.getWidth() / 2 + a.getLength() / 2;
    float aMinZ = a.getZ() - a.getWidth() / 2 - a.getLength() / 2;
    float aMaxZ = a.getZ() + a.getWidth() / 2 + a.getLength() / 2;
    
    float bMinX = b.getX() - b.getWidth() / 2 - b.getLength() / 2;
    float bMaxX = b.getX() + b.getWidth() / 2 + b.getLength() / 2;
    float bMinZ = b.getZ() - b.getWidth() / 2 - b.getLength() / 2;
    float bMaxZ = b.getZ() + b.getWidth() / 2 + b.getLength() / 2;
    
    float d1x = bMinX - aMaxX;
    float d1z = bMinZ - aMaxZ;
    float d2x = aMinX - bMaxX;
    float d2z = aMinZ - bMaxZ;
    
    vmml::Vector2f downLeft {bMinX, bMinZ};
    vmml::Vector2f upLeft {bMinX, bMaxZ};
    vmml::Vector2f downRight {bMaxX, bMinZ};
    vmml::Vector2f upRight {bMaxX, bMaxZ};
    
    if (d1x > 0.0f || d1z > 0.0f || d2x > 0.0f || d2z > 0.0f) {
        return false;
    } else {
        std::cout << "downLeft: " << downLeft << "upLeft: " << upLeft << "downRight: " << downRight << "upRight: " << upRight << std::endl;
        std::cout << "position x: " << a.getX() << "position z: " << a.getZ() << std::endl;
        if (((a.getX() - a.getWidth()/2 <= bMinX + 0.5) || (a.getX() + a.getWidth()/2 >= bMaxX + 0.5)) &&
            (a.getZ() - a.getLength()/2 > bMinZ && a.getZ() - a.getLength()/2 < bMaxZ)) {
            handleCollision(a, Z);
        } else {
            handleCollision(a, X);
        }
        return true;
    }
}

void Collisionhandler::handleCollision(const Entity &a, Side side) {
    std::cout << "Side: " << side << std::endl;
}