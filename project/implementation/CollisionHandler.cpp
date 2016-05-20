#include "CollisionHandler.hpp"

Collisionhandler::Collisionhandler() {
    
}

#pragma mark Collision Test
bool Collisionhandler::testOBBOverlap(const Entity &a, const Entity &b) {
    if (b.getType() == Entity::NOTCOLLIDABLE) {
        return false;
    }
    
    vmml::Vector2f axis1(std::cos(a.getRotation()), std::sin(a.getRotation()));
    vmml::Vector2f axis2(-std::sin(a.getRotation()), std::cos(a.getRotation()));
    vmml::Vector2f axis3(std::cos(b.getRotation()), std::sin(b.getRotation()));
    vmml::Vector2f axis4(-std::sin(b.getRotation()), std::cos(b.getRotation()));
    
    vmml::Vector2f distance = vmml::Vector2f(a.getX(), a.getZ()) - vmml::Vector2f(b.getX(), b.getZ());
    
    float r1, r2, r3, r4;
    
    //projection on axis 1
    r1 = a.getLength() * std::fabs(axis1.dot(axis1));
    r2 = a.getWidth() * std::fabs(axis2.dot(axis1));
    r3 = b.getLength() * std::fabs(axis3.dot(axis1));
    r4 = b.getWidth() * std::fabs(axis4.dot(axis1));
    if (r1 + r2 + r3 + r4 <= std::fabs(distance.dot(axis1))) {return false;};
    
    //projection on axis 2
    r1 = a.getLength() * std::fabs(axis1.dot(axis2));
    r2 = a.getWidth() * std::fabs(axis2.dot(axis2));
    r3 = b.getLength() * std::fabs(axis3.dot(axis2));
    r4 = b.getWidth() * std::fabs(axis4.dot(axis2));
    if (r1 + r2 + r3 + r4 <= std::fabs(distance.dot(axis2))) {return false;};
    
    //projection on axis 3
    r1 = a.getLength() * std::fabs(axis1.dot(axis3));
    r2 = a.getWidth() * std::fabs(axis2.dot(axis3));
    r3 = b.getLength() * std::fabs(axis3.dot(axis3));
    r4 = b.getWidth() * std::fabs(axis4.dot(axis3));
    if (r1 + r2 + r3 + r4 <= std::fabs(distance.dot(axis3))) {return false;};
    
    //projection on axis 4
    r1 = a.getLength() * std::fabs(axis1.dot(axis4));
    r2 = a.getWidth() * std::fabs(axis2.dot(axis4));
    r3 = b.getLength() * std::fabs(axis3.dot(axis4));
    r4 = b.getWidth() * std::fabs(axis4.dot(axis4));
    if (r1 + r2 + r3 + r4 <= std::fabs(distance.dot(axis4))) {return false;};
    
    return true;
}

#pragma mark Collision Handling

void Collisionhandler::handleCollision(const Entity &a, const Entity &b) {
    switch (b.getType()) {
        case Entity::COLLIDABLE:
            switch (getCollisionSide(a, b)) {
                case X_AXIS:
                    collisionForce = vmml::Vector3f(0,0,b.getZ());
                    break;
                case X_AXIS_N:
                    collisionForce = vmml::Vector3f(0,0,-b.getZ());
                    break;
                case Z_AXIS:
                    collisionForce = vmml::Vector3f(b.getX(), 0, 0);
                    break;
                case Z_AXIS_N:
                    collisionForce = vmml::Vector3f(-b.getX(), 0, 0);
                    break;
            }
            break;
        default:
            break;
    }
}

vmml::Vector3f Collisionhandler::getCollisionForce() {
    collisionForce = vmml::normalize(collisionForce);
    return collisionForce;
}

#pragma mark TODO - Implement realistic gravity force
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

#pragma mark Helper functions

vmml::Matrix<2, 2, float> Collisionhandler::getBoundingBox(const Entity &a) {
    vmml::Matrix<2, 2, float> boundingBox;
    
    boundingBox.at(0, 0) = a.getX() - a.getWidth() / 2 - a.getLength() / 2;
    boundingBox.at(0, 1) = a.getX() + a.getWidth() / 2 + a.getLength() / 2;
    boundingBox.at(1, 0) = a.getZ() - a.getWidth() / 2 - a.getLength() / 2;
    boundingBox.at(1, 1) = a.getZ() + a.getWidth() / 2 + a.getLength() / 2;
    
    return boundingBox;
}


Collisionhandler::CollisionSide Collisionhandler::getCollisionSide(const Entity &a, const Entity &b) {
    float x_left = a.getX() - a.getWidth()/2;
    float x_right = (a.getX() + a.getWidth()/2);
    float z_up = (a.getZ() + a.getLength()/2);
    float z_down = a.getZ() - a.getLength()/2 ;
    
    float min_x = boundingBoxB.at(0,0);
    float max_x = boundingBoxB.at(0,1);
    float min_z = boundingBoxB.at(1,0);
    float max_z = boundingBoxB.at(1,1);
    
    if ((x_left >= min_x || x_right <= max_x) && (z_up <= min_z || z_down >= max_z)) {
        if (a.getZ() < 0) {
            if (z_up <= min_z) {
                return X_AXIS;
            } else {
                return X_AXIS_N;
            }
        } else {
            if (z_up <= min_z) {
                return X_AXIS_N;
            } else {
                return X_AXIS;
            }
        }
    } else {
        if (a.getX() < 0) {
            if (x_right <= min_x) {
                return Z_AXIS;
            } else {
                return Z_AXIS_N;
            }
        } else {
            if (x_right <= min_x) {
                return Z_AXIS_N;
            } else {
                return Z_AXIS;
            }
        }
    }
}