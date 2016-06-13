#ifndef Tree_h
#define Tree_h

#include "Entity.hpp"

class Tree : public Entity {
 public:
  Tree(float x, float y, float z, float w, float h, float l, float weight,
       float r, bool col, Type type);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix, vmml::Matrix4f &lightPositionMatrix, bool shadowMode);
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
  virtual void handleCollision(Entity &b);
};

#endif /* Tree_h */