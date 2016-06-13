#ifndef Barrier_h
#define Barrier_h

#include "Entity.hpp"
#include "Helper.hpp"

class Barrier : public Entity {
 public:
  Barrier(float x, float y, float z, float w, float h, float l, float weight,
          float r, bool col, Type type, Direction direction);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix, vmml::Matrix4f &lightPositionMatrix, bool shadowMode);
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
  virtual void handleCollision(Entity &b);

 private:
  Direction direction;
  vmml::Vector3f scaleFactor;
};

#endif /* Barrier_h */
