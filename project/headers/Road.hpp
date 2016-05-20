#ifndef Road_hpp
#define Road_hpp

#include "Entity.hpp"

class Road : public Entity{
    
public:
    Road(float x, float y, float z, float w, float h, float l, float weight, float r, bool col, Type type);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
    virtual void handleCollision(Entity &b);
private:
    bool isPartOfRoad(int x, int z);
};

#endif /* Road_hpp */
