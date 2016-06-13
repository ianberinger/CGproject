#include "Wheel.hpp"

Wheel::Wheel()
    : Entity(0.0f, 0.0f, 0.0f, 1.5, 1, 2.5, 0.0, 0.0, true,
             Entity::Type::NOTCOLLIDABLE) {}

Wheel::Wheel(float x, float y, float z, float w, float h, float l, float weight,
             float r, bool col, Type type, bool ghost)
    : Entity(x, y, z, w, h, l, weight, r, col, type) {
  this->ghost = ghost;
}

void Wheel::draw(Renderer &r, vmml::Matrix4f &modelMatrix, vmml::Matrix4f &lightPositionMatrix, bool shadowMode) {
  r.getObjects()->getShader("wheel")->setUniform("fogColor", fogColor);
  r.getObjects()->getShader("wheel")->setUniform("ghost", ghost);

  r.getModelRenderer()->drawModel(
      "wheel", "camera",
      modelMatrix * vmml::create_translation(getXYZ()) *
          vmml::create_rotation(getRotAngle(), vmml::Vector3f::UNIT_Y) *
          vmml::create_rotation(getComAngle(), vmml::Vector3f::UNIT_X) *
          vmml::create_scaling(vmml::Vector3f(0.5f)),
      std::vector<std::string>({}));
}

void Wheel::update(Renderer &r, bool isPaused, const double &deltaTime) {
  float roll = r.getInput()->getGyroscopeRoll();
  float pitch = r.getInput()->getGyroscopePitch();

  if (deltaTime > 1) {
    setRotAngle(pitch);
  }

  setComAngle(getComAngle() - (roll + 0.75));
}

void Wheel::handleCollision(Entity &b) {
  // do something
}