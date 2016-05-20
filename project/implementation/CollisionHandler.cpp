#include "CollisionHandler.hpp"

Collisionhandler::Collisionhandler() {
    
}

#pragma mark Collision Test
bool Collisionhandler::testOBBOverlap(Entity &a, Entity &b) {
    if (b.getType() == Entity::NOTCOLLIDABLE) {
        return false;
    }
    
    OBB aOBB = createOBB(a);
    OBB bOBB = createOBB(b);
    
    bool didCollide = overlaps(aOBB, bOBB) && overlaps(bOBB, aOBB);
    if (didCollide) {
        a.handleCollision(b);
        b.handleCollision(a);
    }
    return didCollide;
}

#pragma mark Helper functions
Collisionhandler::OBB Collisionhandler::createOBB(const Entity &a) {
    Collisionhandler::OBB a_OBB;
    vmml::Vector2f a_x (cosf(a.getRotation()), sinf(a.getRotation()));
    vmml::Vector2f a_z (-sinf(a.getRotation()), cosf(a.getRotation()));
    
    a_x *= a.getWidth()/2;
    a_z *= a.getLength()/2;
    
    a_OBB.corner[0] = vmml::Vector2f(a.getX(), a.getZ()) - a_x - a_z;
    a_OBB.corner[1] = vmml::Vector2f(a.getX(), a.getZ()) + a_x - a_z;
    a_OBB.corner[2] = vmml::Vector2f(a.getX(), a.getZ()) + a_x + a_z;
    a_OBB.corner[3] = vmml::Vector2f(a.getX(), a.getZ()) - a_x + a_z;
    
    a_OBB.axis[0] = a_OBB.corner[1] - a_OBB.corner[0];
    a_OBB.axis[1] = a_OBB.corner[3] - a_OBB.corner[0];
    
    for (int i = 0; i < 2; i++) {
        a_OBB.axis[i] /= a_OBB.axis[i].squared_length();
        a_OBB.origin[i] = a_OBB.corner[0].dot(a_OBB.axis[i]);
    }
    
    return a_OBB;
}

bool Collisionhandler::overlaps(const OBB &a, const OBB &b) {
    for (int i = 0; i < 2; i++) {
        double t = b.corner[0].dot(a.axis[i]);
        
        double tMin = t;
        double tMax = t;
        
        for (int c = 0; c < 4; c++) {
            t = b.corner[c].dot(a.axis[i]);
            
            if (t < tMin) {
                tMin = t;
            } else if (t > tMax) {
                tMax = t;
            }
        }
        
        if ((tMin > 1 + a.origin[i]) || (tMax < a.origin[i])) {
            return false;
        }
    }
    return true;
}
