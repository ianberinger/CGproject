#ifndef Marker_h
#define Marker_h

#include "Entity.hpp"

enum MarkerType { START, CHECKPOINT };

class Marker : public Entity {
 public:
  Marker(float x, float z, Direction direction, float angle, MarkerType type);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix,
                    vmml::Vector3f &cameraPos, vmml::Vector3f &lightPos);
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
  virtual void handleCollision(Entity &b);
  bool isStart() {
    if (markerType == START) {
      return true;
    }
    return false;
  }
  Direction direction;
  float angle;
  MarkerType markerType;
  bool passed = false;

 private:
};

#endif /* Marker_h */