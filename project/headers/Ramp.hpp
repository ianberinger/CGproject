#ifndef Ramp_h
#define Ramp_h

#include "Entity.hpp"

class Ramp : public Entity {
 public:
  Ramp(float x, float y, float z, float w, float h, float l, float weight,
       float r, bool col, Type type);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix,
                    vmml::Vector3f &cameraPos, vmml::Vector3f &lightPos);
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
  virtual void handleCollision(Entity &b);
};

#endif /* Ramp_h */
