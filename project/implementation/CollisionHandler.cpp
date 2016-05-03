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

bool Collisionhandler::testAABBOverlap(const Entity &a, const Entity &b) {
    
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
        handleCollision(bMaxX, bMinX, bMaxZ, bMinZ, a, b);
        
        return true;
    }
}

void Collisionhandler::handleCollision(float max_x, float min_x, float max_z, float min_z, const Entity &a, const Entity &b) {
    float x_left = a.getX() - a.getWidth()/2;
    float x_right = (a.getX() + a.getWidth()/2);
    float z_up = (a.getZ() + a.getLength()/2);
    float z_down = a.getZ() - a.getLength()/2 ;
    
    collisionForce.x() = 0.0;
    collisionForce.z() = 0.0;
    
    switch (b.getType()) {
        case Entity::RAMP: {
            float rampOccupation = z_up - min_z >= a.getLength() ? 1 : z_up - min_z <= 0 ? 0 : z_up - min_z;
            if (_carHeight < b.getHeight()) {
                _carHeight += b.getHeight()/b.getLength() * rampOccupation;
            }
            _collisionAngle = -std::atan(_carHeight/b.getLength());
            if (z_up >= max_z + b.getLength()/2) {
                gravityFlag = true;
            }
            break;
        }
        case Entity::COLLIDABLE: {
            if ((x_left >= min_x || x_right <= max_x) && (z_up <= min_z || z_down >= max_z)) {
                if (a.getZ() < 0) {
                    if (z_up <= min_z) {
                        collisionForce = vmml::Vector3f(0,0,b.getZ());
                    } else {
                        collisionForce = vmml::Vector3f(0,0,-b.getZ());
                    }
                } else {
                    if (z_up <= min_z) {
                        collisionForce = vmml::Vector3f(0,0,-b.getZ());
                    } else {
                        collisionForce = vmml::Vector3f(0,0,b.getZ());
                    }
                }
            } else if ((z_up <= max_z || z_down >= min_z) && (x_right >= max_x || x_right <= min_x)){
                if (a.getX() < 0) {
                    if (x_right <= min_x) {
                        collisionForce = vmml::Vector3f(b.getX(), 0, 0);
                    } else {
                        collisionForce = vmml::Vector3f(-b.getX(), 0, 0);
                    }
                } else {
                    if (x_right <= min_x) {
                        collisionForce = vmml::Vector3f(-b.getX(), 0, 0);
                    } else {
                        collisionForce = vmml::Vector3f(b.getX(), 0, 0);
                    }
                }
            }
            break;
        }
    }
    
}

vmml::Vector3f Collisionhandler::getCollisionForce() {
    collisionForce = vmml::normalize(collisionForce);
    collisionForce.y() = _collisionAngle;
    return collisionForce;
}

void Collisionhandler::applyGravity() {
    if (gravityFlag) {
        _collisionAngle = (std::abs(_collisionAngle) - 0.1)*-1;
        std::cout << "collision angle: " << _collisionAngle << std::endl;
        _carHeight = _carHeight - 0.1;
    }
    if (std::abs(_carHeight) < 0.2) {
        gravityFlag = false;
        _carHeight = 0.0;
        _collisionAngle = 0.0;
    }
}
