#ifndef CollisionHandler_hpp
#define CollisionHandler_hpp

#include <iostream>
#include "Entity.hpp"
#include "vmmlib/util.hpp"

class Collisionhandler {
public:
    Collisionhandler();
    
    /**
     *  An oriented bounding box
     *
     */
    struct OBB {
        vmml::Vector2f corner[4]; /**< Corners of the box, where 0 is the lower left. */
        vmml::Vector2f axis[2];  /**< Two edges of the box extended away from corner[0] */
        double origin[2];
    };
    /**
     *  Checks if an entity a collides with an entity b.
     *
     *  @param a: Entity in 3D coordinate system
     *  @param b: Entity in 3D coordinate system
     *
     *  @return True if there was a collision, false otherwise
     */    
    bool testOBBOverlap(Entity &a, Entity &b);
private:
    /**
     *  Creates an Oriented bounding box for an entity
     *
     *  @param a Entity from which the OBB should be created
     *  @return OBB An oriented bounding box
     */
    OBB createOBB(const Entity &a);
    
    /**
     *  Checks if OBB a has overlapping axes with OBB b
     *
     *  @param a OBB for entity a
     *  @param b OBB for entity b
     *  @return True if there are overlapping, false otherwise
     */
    bool overlaps(const OBB &a, const OBB &b);
};

#endif /* CollisionHandler_hpp */
