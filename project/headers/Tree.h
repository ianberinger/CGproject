//
//  Tree.h
//  bRenderer_ios
//
//  Created by Ian Beringer on 5/3/16.
//
//

#ifndef Tree_h
#define Tree_h

#include "Entity.h"


class Tree : public Entity{
    
public:
    Tree(float x, float y, float z, float w, float h, float l, bool col, Type type);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, const vmml::Vector3f &collisionForce);
    
};

#endif /* Tree_h */