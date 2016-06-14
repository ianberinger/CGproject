#ifndef Wheel_h
#define Wheel_h

#include "Entity.hpp"

class Wheel : public Entity {
 public:
  Wheel();
  Wheel(float x, float y, float z, float w, float h, float l, float weight,
        float r, bool col, Type type, bool ghost);

  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix,
                    vmml::Vector3f &cameraPos, vmml::Vector3f &lightPos);
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
  virtual void handleCollision(Entity &b);

  void setRotAngle(float ang) { rotAngle = ang; }
  float getRotAngle() { return rotAngle; }

  void setComAngle(float ang) { comAngle = ang; }
  float getComAngle() { return comAngle; }

 private:
  bool ghost;
  float rotAngle;
  float comAngle;
  ShaderPtr shader;
};

#endif /* Wheel_h */
