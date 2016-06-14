#include "Tree.hpp"

Tree::Tree(float x, float y, float z, float w, float h, float l, float weight,
           float r, bool col, Type type)
    : Entity(x, y, z, w, h, l, weight, r, col, type) {}

void Tree::draw(Renderer &r, vmml::Matrix4f &modelMatrix, vmml::Matrix4f &lightPositionMatrix, bool shadowMode) {
  if (shadowMode) {
    std::cout << "In shadow mode" << std::endl;
    r.getObjects()->getShader("tree_trunk")->setUniform("RenderMode", 1.0f);
    r.getModelRenderer()->drawModel(
                                    "tree_trunk", "camera",
                                    modelMatrix * vmml::create_translation(getXYZ()) *
                                    vmml::create_scaling(vmml::Vector3f(0.1f, 0.1f, 0.1f)),
                                    std::vector<std::string>({}));
    r.getObjects()->getShader("tree_top")->setUniform("RenderMode", 1.0f);
    r.getModelRenderer()->drawModel(
                                    "tree_top", "camera",
                                    modelMatrix * vmml::create_translation(getXYZ()) *
                                    vmml::create_scaling(vmml::Vector3f(0.1f, 0.1f, 0.1f)),
                                    std::vector<std::string>({}));
  } else {
    std::cout << "In normal mode" << std::endl;
    r.getObjects()->getShader("tree_trunk")->setUniform("LightSpaceMatrix", lightPositionMatrix);
    r.getObjects()->getShader("tree_trunk")->setUniform("fogColor", fogColor);
    r.getObjects()->getShader("tree_trunk")->setUniform("EyeVec", r.getObjects()->getCamera("camera")->getPosition());
    r.getObjects()->getShader("tree_trunk")->setUniform("LightPos", r.getObjects()->getLight("light")->getPosition());
    r.getObjects()->getShader("tree_trunk")->setUniform("RenderMode", 0.0f);
    r.getObjects()->getShader("tree_trunk")->setUniform("DepthMap", r.getObjects()->getDepthMap("DepthMap"));
    r.getModelRenderer()->drawModel(
                                    "tree_trunk", "camera",
                                    modelMatrix * vmml::create_translation(getXYZ()) *
                                    vmml::create_scaling(vmml::Vector3f(0.1f, 0.1f, 0.1f)),
                                    std::vector<std::string>({}));
    r.getObjects()->getShader("tree_top")->setUniform("LightSpaceMatrix", lightPositionMatrix);
    r.getObjects()->getShader("tree_top")->setUniform("RenderMode", 0.0f);
    r.getObjects()->getShader("tree_top")->setUniform("fogColor", fogColor);
    r.getObjects()->getShader("tree_top")->setUniform("EyeVec", r.getObjects()->getCamera("camera")->getPosition());
    r.getObjects()->getShader("tree_top")->setUniform("LightPos", r.getObjects()->getLight("light")->getPosition());
    r.getModelRenderer()->drawModel(
                                    "tree_top", "camera",
                                    modelMatrix * vmml::create_translation(getXYZ()) *
                                    vmml::create_scaling(vmml::Vector3f(0.1f, 0.1f, 0.1f)),
                                    std::vector<std::string>({}));
  }
}

void Tree::update(Renderer &r, bool isPaused, const double &deltaTime) {
  // do something
}

void Tree::handleCollision(Entity &b) {
  // do something
}