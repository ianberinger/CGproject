//
//  Emitter.hpp
//  bRenderer_ios
//
//  Created by Timothée Wildhaber on 16.05.16.
//
//

#ifndef Emitter_hpp
#define Emitter_hpp
#define NUM_PARTICLES 180


#include "Entity.h"


typedef struct Particle
{
    float pID;
    float pRadiusOffset;
    float pVelocityOffset;
    float pDecayOffset;
    float pSizeOffset;
    vmml::Vector3f pColorOffset;
}
Particle;

typedef struct Emitter
{
    Particle eParticles[NUM_PARTICLES];
    float eRadius;
    float eVelocity;
    float eDecay;
    float eSize;
    vmml::Vector3f eColor;
    vmml::Vector4f ePosition;
}
Emitter;

class EmitterObject : public Entity{
    
public:
    EmitterObject(float x, float y, float z);
    virtual void draw(Renderer &r,vmml::Matrix4f &modelMatrix);
    virtual void update(Renderer &r, bool isPaused, const double &deltaTime);
    vmml::Vector3f gravity;
    float life;
    float time;
    Emitter emitter;
private:
    float randomFloatBetween(float a, float b){
        float range = b - a;
        return (((float) (arc4random() % ((unsigned)RAND_MAX + 1)) / RAND_MAX) * range) + a;};
};




#endif /* Emitter_hpp */
