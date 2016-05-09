//
//  Ramp.h
//  bRenderer_ios
//
//  Created by Lukas Vollenweider on 03/05/16.
//
//

#ifndef Ramp_h
#define Ramp_h

#include "Entity.h"


class Ramp : public Entity{
    
public:
    Ramp(float x, float y, float z, float w, float h, float l, bool col, Type type);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r);
    
};

#endif /* Ramp_h */
