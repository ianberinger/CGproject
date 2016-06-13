#ifndef Enitity_h
#define Enitity_h

#include <iostream>
#include <string>
#include "Renderer.h"

enum Direction { UP, LEFT, RIGHT, DOWN = 4 };
const float translateFactor = 4.0;

class Entity {
 public:
  enum Type { NOTCOLLIDABLE, COLLIDABLE, RAMP };

  Entity(float x, float y, float z, float w, float h, float l, float weight,
         float r, bool col, Type type) {
    setX(x * translateFactor);
    setY(y);
    setZ(z * translateFactor);
    setWidth(w);
    setHeight(h);
    setLength(l);
    setWeight(weight);
    setRotation(r);
    setCollision(col);
    setType(type);
  }

  virtual ~Entity() {}

  const vmml::Vector4f fogColor = vmml::Vector4f(0.5, 0.5, 0.5, 1);

  void setX(float x1) { x = x1; }
  void setY(float y1) { y = y1; }
  void setZ(float z1) { z = z1; }

  void setWidth(float w) { width = w; };
  void setHeight(float h) { height = h; }
  void setLength(float l) { length = l; }

  void setWeight(float weight) { this->weight = weight; };
  void setRotation(float r) { rotation = r; };

  void setType(Type t) { type = t; };

  void setCollision(bool col) { collision = col; }

  float getX() const { return x; }
  float getY() const { return y; }
  float getZ() const { return z; }
  vmml::Vector3f getXYZ() const { return vmml::Vector3f(x, y, z); }

  float getWidth() const { return width; }
  float getHeight() const { return height; }
  float getLength() const { return length; }
  float getWeight() const { return weight; }

  float getRotation() const { return rotation; }

  bool hasCollision() { return collision; }

  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix, vmml::Matrix4f &lightPositionMatrix, bool shadowMode) = 0;
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime) = 0;
  /**
   *  Handles the collision with object b
   *
   *  @pre Collision happened
   *
   *  @param Entity Entity with which the object collided
   */
  virtual void handleCollision(Entity &b) = 0;

  Type getType() const { return type; };

 private:
  float x;
  float y;
  float z;
  float width;
  float height;
  float length;
  float weight;
  // in radian
  float rotation;
  Type type;

  bool collision;
};

#endif /* Enitity_h */
