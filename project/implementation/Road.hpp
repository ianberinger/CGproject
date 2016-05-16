//
//  Road.hpp
//  bRenderer_ios
//
//  Created by Lukas Vollenweider on 16/05/16.
//
//

#ifndef Road_hpp
#define Road_hpp

#include "Entity.h"

class Road : public Entity{
    
public:
    Road(float x, float y, float z, float w, float h, float l, bool col, Type type);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
private:
    bool isPartOfRoad(int x, int z);
};

#endif /* Road_hpp */
