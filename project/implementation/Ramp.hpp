//
//  Ramp.hpp
//  bRenderer_ios
//
//  Created by Lukas Vollenweider on 02/05/16.
//
//

#ifndef Ramp_hpp
#define Ramp_hpp

#include "Entity.h"


class Ramp : public Entity{
    
public:
    Ramp(float x, float y, float z, float w, float h, float l, bool col, Type type);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, const vmml::Vector3f &collisionForce);
    
};
#endif /* Ramp_hpp */
