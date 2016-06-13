//
//  sphere.hpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 13.06.16.
//
//

#ifndef sphere_hpp
#define sphere_hpp

#include "Entity.hpp"

class Sphere : public Entity {
    
public:
    Sphere();
    virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
    virtual void handleCollision(Entity &b);
    bool state;

}


#endif /* sphere_hpp */
