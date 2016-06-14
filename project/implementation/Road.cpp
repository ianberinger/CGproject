#include "Barrier.hpp"
#include "Game.hpp"
#include "Road.hpp"

Road::Road(float x, float y, float z, float w, float h, float l, float weight,
           float r, bool col, Type type)
    : Entity(x, y, z, w, h, l, weight, r, col, type) {}

void Road::draw(Renderer &r, vmml::Matrix4f &modelMatrix) {
  r.getObjects()->getShader("road")->setUniform("fogColor", fogColor);
  r.getObjects()->getShader("road")->setUniform(
      "EyeVec", r.getObjects()->getCamera("camera")->getPosition());
  r.getObjects()->getShader("road")->setUniform(
      "LightPos", r.getObjects()->getLight("light")->getPosition());

  int x_cord = getX();
  int z_cord = getZ();
  int stretchvalue = 1;
  while (isPartOfRoad(x_cord, z_cord)) {
    z_cord += 1;
    stretchvalue += 1;
  }
  // bRenderer::log("Stretch:" + std::to_string(stretchvalue) + " length:" +
  // std::to_string(getLength()));

  r.getObjects()->getShader("road")->setUniform(
      "ScaleFactor", vmml::Vector3f(2.0f, 1.0f, stretchvalue / 2 + 2));

  r.getModelRenderer()->drawModel(
      "plate", "camera",
      modelMatrix * vmml::create_translation(vmml::Vector3f(
                        getX(), getY() + 0.1, getZ() + stretchvalue / 2 - 1)) *
          vmml::create_scaling(
              vmml::Vector3f(2.0f, 1.0f, stretchvalue / 2 + 2)),
      std::vector<std::string>({}));
}

void Road::update(Renderer &r, bool isPaused, const double &deltaTime) {
  // do something
}

void Road::handleCollision(Entity &b) {
  // do something
}

bool Road::isPartOfRoad(int x, int z) {
  int v = Game::_map[(int)(x / (int)(translateFactor))][(
      int)(z / (int)(translateFactor))];
  if (v != 4 && v != 6) {
    return true;
  } else {
    return false;
  }
}