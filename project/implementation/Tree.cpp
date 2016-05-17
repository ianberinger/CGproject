#include "Tree.hpp"

Tree::Tree(float x, float y, float z, float w, float h, float l, bool col, Type type):Entity(x, y, z, w, h, l, col, type){
    
}

void Tree::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
    ShaderPtr treeShader = r.getObjects()->getShader("tree");
    treeShader->setUniform("fogColor", fogColor);
    
    
    r.getModelRenderer()->drawModel("tree", "camera", modelMatrix*vmml::create_translation(getXYZ())*vmml::create_scaling(vmml::Vector3f(0.02f,0.02f,0.02f)), std::vector<std::string>({ }));
    
}

void Tree::update(Renderer &r, bool isPaused, const double &deltaTime){
    //do something
    
}