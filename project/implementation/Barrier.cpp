#include "Barrier.hpp"

Barrier::Barrier(float x, float y, float z, float w, float h, float l, float weight, float r, bool col, Type type, Direction dir):Entity(x, y, z, w, h, l, weight, r, col, type){
    direction = dir;
}

 void Barrier::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
     ShaderPtr barrierShader = r.getObjects()->getShader("barrier");
     barrierShader->setUniform("fogColor", fogColor);
     //bRenderer::log("turn: "+ std::to_string(direction*M_PI_F/2.0f));
     
     float rotation = 3.0f;
     
     setRotation(-rotation);
     setLength(12.0f);
     
     r.getModelRenderer()->drawModel("Barrier", "camera", modelMatrix*vmml::create_translation(getXYZ())*vmml::create_rotation(rotation, vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(1, 1, 6)), std::vector<std::string>({ }));
     }


void Barrier::update(Renderer &r, bool isPaused, const double &deltaTime){
//do something
}

void Barrier::handleCollision(Entity &b){
    std::cout << "MY W: " << getWeight() << std::endl;
}