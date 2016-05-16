//
//  Emitter.cpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 16.05.16.
//
//

#include "Emitter.h"



EmitterObject::EmitterObject(float x, float y, float z):Entity(x, y, z, 0.1,0.1,0.1,false,Entity::Type::NOTCOLLIDABLE){
    
        Emitter newEmitter = {0.0f};
    
    float oRadius = 0.10f;
    float oVelocity = 0.50f;
    float oDecay = 0.25f;
    float oSize = 8.00f;
    float oColor = 0.25f;
    
    
    for(int i=0; i<NUM_PARTICLES; i++)
    {
        newEmitter.eParticles[i].pID = (((float)i/(float)NUM_PARTICLES)*2*M_PI_F);
        
        newEmitter.eParticles[i].pRadiusOffset = randomFloatBetween(oRadius,1.00f);
        newEmitter.eParticles[i].pVelocityOffset = randomFloatBetween(-oVelocity,oVelocity);
        newEmitter.eParticles[i].pDecayOffset = randomFloatBetween(-oDecay,oDecay);
        newEmitter.eParticles[i].pSizeOffset = randomFloatBetween(-oSize,oSize);
        float r = randomFloatBetween(0.0,oColor);
        newEmitter.eParticles[i].pColorOffset = vmml::Vector3f(r,r,r);
    }
    
    
    newEmitter.eRadius = 0.75f;
    newEmitter.eVelocity = 0.50f;
    newEmitter.eDecay = 2.00f;
    newEmitter.eSize = 2.00f;
    newEmitter.eColor = vmml::Vector3f(1.00f, 0.50f, 0.00f);
    
    // 6
    // Set global factors
    float growth = newEmitter.eRadius / newEmitter.eVelocity;
    life = growth + newEmitter.eDecay + oDecay;
    
    float drag = 1.00f;
    gravity = vmml::Vector3f(0.00f, -0.81f*(1.0f/drag),0.0f);
    
        emitter=newEmitter;
    
    GLuint particleBuffer = 0;
    glGenBuffers(1, &particleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, particleBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(emitter.eParticles), emitter.eParticles, GL_STATIC_DRAW);
    
}

void EmitterObject::draw(Renderer &r, vmml::Matrix4f &modelMatrix){

    

    emitter.ePosition=vmml::Vector4f((44*4-100),0.5,(4*4-100));
    
    ShaderPtr pShader = r.getObjects()->getShader("particles");
    pShader->setUniform("u_ProjectionMatrix", r.getObjects()->getCamera("camera")->getProjectionMatrix());
    pShader->setUniform("u_ModelViewMatrix", r.getObjects()->getCamera("camera")->getViewMatrix()*modelMatrix);
    pShader->setUniform("u_Gravity", gravity);
    pShader->setUniform("u_Time", time);
    pShader->setUniform("u_eRadius", emitter.eRadius);
    pShader->setUniform("u_eVelocity", emitter.eVelocity);
    pShader->setUniform("u_eDecay", emitter.eDecay);
    pShader->setUniform("u_eSize", emitter.eSize);
    pShader->setUniform("u_eColor", emitter.eColor);

    pShader->registerAttrib("a_pID", 1, GL_FLOAT, sizeof(Particle), offsetof(Particle, pID));
    pShader->registerAttrib("a_pRadiusOffset", 1, GL_FLOAT, sizeof(Particle), offsetof(Particle, pRadiusOffset));
    pShader->registerAttrib("a_pVelocityOffset", 1, GL_FLOAT, sizeof(Particle), offsetof(Particle, pVelocityOffset));
    pShader->registerAttrib("a_pDecayOffset", 1, GL_FLOAT, sizeof(Particle), offsetof(Particle, pDecayOffset));
    pShader->registerAttrib("a_pSizeOffset", 1, GL_FLOAT, sizeof(Particle), offsetof(Particle, pSizeOffset));
    pShader->registerAttrib("a_pColorOffset", 3, GL_FLOAT, sizeof(Particle), offsetof(Particle, pColorOffset));
    pShader->registerAttrib("a_position", 4, GL_FLOAT, sizeof(Particle), offsetof(Emitter, ePosition));
    

    pShader->bind();
    //glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);

    
    
}



void EmitterObject::update(Renderer &r, bool isPaused, const double &deltaTime){

    time=time+deltaTime;
    
    if(time > life){
        time = 0.0f;
    }

}