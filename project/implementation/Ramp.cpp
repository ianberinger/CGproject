#include "Ramp.hpp"

Ramp::Ramp(float x, float y, float z, float w, float h, float l, float weight,
           float r, bool col, Type type)
    : Entity(x, y, z, w, h, l, weight, r, col, type) {}

void Ramp::draw(Renderer &r, vmml::Matrix4f &modelMatrix) {
  r.getObjects()->getShader("ramp")->setUniform("fogColor", fogColor);

  r.getModelRenderer()->drawModel(
      "ramp", "camera", modelMatrix * vmml::create_translation(getXYZ()),
      std::vector<std::string>({}));
}

void Ramp::update(Renderer &r, bool isPaused, const double &deltaTime) {
  // do something
}

void Ramp::handleCollision(Entity &b) {
  // do something
}