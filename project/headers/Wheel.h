//
//  Wheel.h
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 21.04.16.
//
//

#ifndef Wheel_h
#define Wheel_h

#include "Entity.h"

class Wheel : public Entity{
public:
    Wheel();
    Wheel(float x, float y, float z, float w, float h, float l, bool col, Type type);
    
    virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
    
    void setRotAngle(float ang){rotAngle=ang;}
    float getRotAngle(){return rotAngle;}
    
    
    void setComAngle(float ang){comAngle=ang;}
    float getComAngle(){return comAngle;}

    
private:

    float rotAngle;
    float comAngle;
    
};

#endif /* Wheel_h */



