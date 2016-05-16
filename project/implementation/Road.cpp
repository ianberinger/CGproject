//
//  Road.cpp
//  bRenderer_ios
//
//  Created by Lukas Vollenweider on 16/05/16.
//
//

#include "Road.hpp"
#include "Barrier.h"
#include "Game.h"

Road::Road(float x, float y, float z, float w, float h, float l, bool col, Type type):Entity(x, y, z, w, h, l, col, type){
    
    
}

void Road::draw(Renderer &r,vmml::Matrix4f &modelMatrix){
    ShaderPtr roadShader = r.getObjects()->getShader("road");
    roadShader->setUniform("fogColor", fogColor);
    
    int x_cord = getX();
    int z_cord = getZ();
    int stretchvalue = 1;
    while (isPartOfRoad(x_cord, z_cord)) {
        z_cord += 1;
        stretchvalue += 1;
    }
    r.getModelRenderer()->drawModel("Plate", "camera", modelMatrix*vmml::create_translation(vmml::Vector3f(getX(), getY(), getZ()+stretchvalue/2-1))*vmml::create_scaling(vmml::Vector3f(1.1f, 0.1f, stretchvalue/2+2)), std::vector<std::string>({ }));
}

void Road::update(Renderer &r, bool isPaused, const double &deltaTime){
    //do something
    
}

bool Road::isPartOfRoad(int x, int z) {
    if (Game::_map[(int)(x + 100)/4][(int)(z + 100)/4] != 4) {
        return true;
    } else {
        return false;
    }
}