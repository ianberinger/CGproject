//
//  Barrier.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#ifndef Barrier_h
#define Barrier_h


#endif /* Barrier_h */

#include "Entity.h"


class Barrier : public Entity{

public:
    Barrier(float x, float y, float z, float w, float h, float l, bool col);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, const vmml::Vector3f &collisionForce);

};