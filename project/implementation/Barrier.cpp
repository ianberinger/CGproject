#include "Barrier.hpp"

Barrier::Barrier(float x, float y, float z, float w, float h, float l,
                 float weight, float r, bool col, Type type, Direction dir)
    : Entity(x, y, z, w, h, l, weight, r, col, type) {
  direction = dir;
  float rotation = direction * M_PI_F / 2.0f;
  setRotation(-rotation);
  setLength(getLength() * 2.0);
  scaleFactor = vmml::Vector3f(0.5);
}
void Barrier::draw(Renderer &r, vmml::Matrix4f &modelMatrix) {}

void Barrier::draw(Renderer &r, vmml::Matrix4f &modelMatrix,
                   vmml::Vector3f &cameraPos, vmml::Vector3f &lightPos) {
  if (shader == nullptr) {
    shader = r.getObjects()->getShader("fence");
    shader->setUniform("fogColor", fogColor);
  }
  // r.getObjects()->getShader("fence")->setUniform("ScaleFactor", scaleFactor);
  shader->setUniform("EyeVec", cameraPos);
  shader->setUniform("LightPos", lightPos);

  // bRenderer::log("turn: "+ std::to_string(direction*M_PI_F/2.0f));

  r.getModelRenderer()->drawModel(
      "fence", "camera",
      modelMatrix * vmml::create_translation(getXYZ()) *
          vmml::create_rotation(-getRotation(), vmml::Vector3f::UNIT_Y) *
          vmml::create_scaling(scaleFactor),
      std::vector<std::string>({}));
}

void Barrier::update(Renderer &r, bool isPaused, const double &deltaTime) {
  // do something
}

void Barrier::handleCollision(Entity &b) {}