#ifndef Player_h
#define Player_h

#include "CollisionHandler.hpp"
#include "Emitter.hpp"
#include "Entity.hpp"
#include "Wheel.hpp"

class Player : public Entity {
 public:
  Player(bool ghost);
  virtual void draw(Renderer &r, vmml::Matrix4f &modelMatrix);
  virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
  virtual void handleCollision(Entity &b);
  void setRotAngle(float ang) { rotAngle = ang; }
  float getRotAngle() { return rotAngle; }

  void setAddAngle(float ang) {
    if (ang > 0.3) {
      addAngle = 0.3;
    } else if (ang < -0.3) {
      addAngle = -0.3;
    } else {
      addAngle = ang;
    }
  }
  float getAddAngle() { return addAngle; }

  void setComAngle(float ang) { comAngle = ang; }
  float getComAngle() { return comAngle; }

  void setVelocity(float vel) { velocity = vel; }
  float getVelocity() { return velocity; }

  void setAcceleration(float acc) { acceleration = acc; }
  float getAcceleration() { return acceleration; }

  void setCollisionHandler(Collisionhandler *handler) {
    collisionHandler = handler;
  }

 private:
  const float minSpeed = -0.2;
  const float maxSpeed = 0.7;
  float rotAngle;
  float addAngle;
  float comAngle;
  float velocity;
  float acceleration;
  float angleAdaption;
  std::vector<std::shared_ptr<Wheel>> wheels;
  Collisionhandler *collisionHandler;
  std::shared_ptr<EmitterObject> emitterObj;
  bool ghost;
};

#endif /* Player_h */
