//
//  Barrier.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#ifndef Barrier_h
#define Barrier_h

#include "Entity.h"
#include "Helper.h"

class Barrier : public Entity{
    
public:
    Barrier(float x, float y, float z, float w, float h, float l, bool col, Type type, Direction direction);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
    
private:
    Direction direction;
};

#endif /* Barrier_h */
