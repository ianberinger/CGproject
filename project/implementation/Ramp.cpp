#include "Ramp.hpp"

Ramp::Ramp(float x, float y, float z, float w, float h, float l, float r, bool col, Type type):Entity(x, y, z, w, h, l, r, col, type){
    
    
}

void Ramp::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
    ShaderPtr rampShader = r.getObjects()->getShader("ramp");
    rampShader->setUniform("fogColor", fogColor);
    
    r.getModelRenderer()->drawModel("ramp", "camera", modelMatrix*vmml::create_translation(getXYZ()), std::vector<std::string>({ }));
}

void Ramp::update(Renderer &r, bool isPaused, const double &deltaTime){
    //do something
    
}

