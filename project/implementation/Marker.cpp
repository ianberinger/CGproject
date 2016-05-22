#include "Marker.hpp"

Marker::Marker(float x, float z, Direction direction, float angle,
               MarkerType type)
    : Entity(x, 0, z, 1, 1, 1, 0.0, 0.0, true, Entity::COLLIDABLE) {
  this->direction = direction;
  this->angle = angle;
  this->markerType = type;
}

void Marker::draw(Renderer &r, vmml::Matrix4f &modelMatrix) {
  // TODO display something nice
}

void Marker::update(Renderer &r, bool isPaused, const double &deltaTime) {
  // do something
}

void Marker::handleCollision(Entity &b) {
  bRenderer::log("marker collision");
  passed = true;
}