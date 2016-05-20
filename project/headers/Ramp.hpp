#ifndef Ramp_h
#define Ramp_h

#include "Entity.hpp"


class Ramp : public Entity{
    
public:
    Ramp(float x, float y, float z, float w, float h, float l, float r, bool col, Type type);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
    
};

#endif /* Ramp_h */
