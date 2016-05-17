#ifndef CollisionHandler_hpp
#define CollisionHandler_hpp

#include <iostream>
#include "Entity.hpp"
#include "vmmlib/util.hpp"

class Collisionhandler {
public:
    Collisionhandler();
    /**
     *  Checks if an entity a collides with an entity b.
     *
     *  @param a: Entity in 3D coordinate system
     *  @param b: Entity in 3D coordinate system
     *
     *  @return True if there was a collision, false otherwise
     */
    bool testAABBOverlap(const Entity &a, const Entity &b);
    
    /**
     *  Returns the collision force which affects the direction when a player collides with a collidable object
     *
     *  @return Vector which points orthonormal to the player
     */
    vmml::Vector3f getCollisionForce();
    void applyGravity();
private:
    enum CollisionSide { X_AXIS, X_AXIS_N, Z_AXIS, Z_AXIS_N };
    vmml::Vector3f collisionForce;
    vmml::Matrix<2, 2, float> boundingBoxA;
    vmml::Matrix<2, 2, float> boundingBoxB;
    float _collisionAngle = 0.0;
    float _carHeight = 0.0;
    bool gravityFlag = false;
    /**
     *  Handles the collision.
     *  If the player collides with a collidable object, the player slows down and the direction gets affected by the collision force.
     *  If the player collides with a ramp, he slows down but the car get lifted
     *
     *  @param a: Entity in 3D coordinate system
     *  @param b: Entity in 3D coordinate system
     */
    void handleCollision(const Entity &a, const Entity &b);
    
    /**
     *  Get the side from entity b with which entity a collides.
     *
     *  @param a: Entity in 3D coordinate system
     *  @param b: Entity in 3D coordinate system
     *  @return CollisionSide (X_AXIS, X_AXIS_N, Z_AXIS, Z_AXIS_N), where N means that the normal vector which is orthogonal to entity a has to be negative.
     */
    CollisionSide getCollisionSide(const Entity &a, const Entity &b);
    
    /**
     *  Defines a rectangular area around the entity
     *
     *  @param a: Entity in 3D coordinate system
     *  @return 2x2 Matrix which represents the rectangular area.
     *          The first row contains the x values (min, max)
     *          The second row contains the z values (min, max)
     */
    vmml::Matrix<2, 2, float> getBoundingBox(const Entity &a);
};

#endif /* CollisionHandler_hpp */
