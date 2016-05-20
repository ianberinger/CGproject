#include "Barrier.hpp"

Barrier::Barrier(float x, float y, float z, float w, float h, float l, float weight, float r, bool col, Type type, Direction dir):Entity(x, y, z, w, h, l, weight, r, col, type){
    direction = dir;
    float rotation = direction*M_PI_F/2.0f;
    setRotation(-rotation);
    setLength(getLength() * 2.0);
}

 void Barrier::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
     r.getObjects()->getShader("barrier")->setUniform("fogColor", fogColor);
     //bRenderer::log("turn: "+ std::to_string(direction*M_PI_F/2.0f));
     
     
     r.getModelRenderer()->drawModel("Barrier", "camera", modelMatrix*vmml::create_translation(getXYZ())*vmml::create_rotation(-getRotation(), vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(getWidth(), getHeight(), getLength()/2.0)), std::vector<std::string>({ }));
     }


void Barrier::update(Renderer &r, bool isPaused, const double &deltaTime){
//do something
}

void Barrier::handleCollision(Entity &b){}