#include "Tree.hpp"

Tree::Tree(float x, float y, float z, float w, float h, float l, float weight,
           float r, bool col, Type type)
    : Entity(x, y, z, w, h, l, weight, r, col, type) {}

void Tree::draw(Renderer &r, vmml::Matrix4f &modelMatrix) {}

void Tree::draw(Renderer &r, vmml::Matrix4f &modelMatrix,
                vmml::Vector3f &cameraPos, vmml::Vector3f &lightPos) {
  if (shaderTrunk == nullptr) {
    shaderTrunk = r.getObjects()->getShader("tree_trunk");
    shaderTrunk->setUniform("fogColor", fogColor);
  }
  if (shaderTop == nullptr) {
    shaderTop = r.getObjects()->getShader("tree_top");
    shaderTop->setUniform("fogColor", fogColor);
  }
  shaderTrunk->setUniform("EyeVec", cameraPos);
  shaderTrunk->setUniform("LightPos", lightPos);
  shaderTop->setUniform("EyeVec", cameraPos);
  shaderTop->setUniform("LightPos", lightPos);
  r.getModelRenderer()->drawModel(
      "tree_trunk", "camera",
      modelMatrix * vmml::create_translation(getXYZ()) *
          vmml::create_scaling(vmml::Vector3f(0.1f, 0.1f, 0.1f)),
      std::vector<std::string>({}));

  r.getModelRenderer()->drawModel(
      "tree_top", "camera",
      modelMatrix * vmml::create_translation(getXYZ()) *
          vmml::create_scaling(vmml::Vector3f(0.1f, 0.1f, 0.1f)),
      std::vector<std::string>({}));
}

void Tree::update(Renderer &r, bool isPaused, const double &deltaTime) {
  // do something
}

void Tree::handleCollision(Entity &b) {
  // do something
}