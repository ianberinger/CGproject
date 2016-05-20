#include "Player.hpp"
#include "Helper.hpp"

Helper h;

Player::Player():Entity(0.0f, 0.0f, 0.0f, 1.0, 1, 2.0, 0.0, true, Entity::Type::NOTCOLLIDABLE){
    
    //wheels for the car
    std::shared_ptr<Wheel> w1( new Wheel(0.55,1.4,1.0,1,1,1,0.0,true, Entity::Type::NOTCOLLIDABLE) );
    std::shared_ptr<Wheel> w2( new Wheel(-0.5,1.4,1.0,1,1,1,0.0,true, Entity::Type::NOTCOLLIDABLE) );
    std::shared_ptr<Wheel> w3( new Wheel(0.525,1.4,-0.68,1,1,1,0.0,true, Entity::Type::NOTCOLLIDABLE) );
    std::shared_ptr<Wheel> w4( new Wheel(-0.475,1.4,-0.68,1,1,1,0.0,true,Entity::Type::NOTCOLLIDABLE) );
    
    emitterObj = std::make_shared<EmitterObject>(-1.9,0.5,-2.5);

    
    wheels.push_back(w1);
    wheels.push_back(w2);
    wheels.push_back(w3);
    wheels.push_back(w4);
    
}

Player::Player(float x, float y, float z, float w, float h, float l, float r, bool col, Type type):Entity(x, y, z, w, h, l,r, col, type){
    setVelocity(0);
    setAcceleration(0);
    
}

void Player::draw(Renderer &r, vmml::Matrix4f &modelMatrix){
    
    ShaderPtr guyShader = r.getObjects()->getShader("car");
    guyShader->setUniform("fogColor", this->fogColor);
    
    collisionHandler->applyGravity();
    
    vmml::Matrix4f transformationMatrix{modelMatrix};
    transformationMatrix *= vmml::create_translation(getXYZ())*vmml::create_rotation(getAddAngle()+getComAngle(), vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(0.75f));
    
    for(auto e : wheels){
        e->draw(r, transformationMatrix);
        
    }
    
    emitterObj->draw(r, transformationMatrix);
    
    r.getModelRenderer()->drawModel("car", "camera", transformationMatrix, std::vector<std::string>({ }));
    
}

void Player::update(Renderer &r, bool isPaused, const double &deltaTime){
    //Getting the inputs from the gyro sensor
    float roll = r.getInput()->getGyroscopeRoll(); // tilt
    float pitch = r.getInput()->getGyroscopePitch(); // left / right
    /*bRenderer::log("roll:" + std::to_string(roll));
     bRenderer::log("pitch:" + std::to_string(pitch));*/

    setVelocity(h.clip(getVelocity()+((roll+0.75)/20), minSpeed ,maxSpeed));
    
    if (isPaused) {
        roll = 0.0;
        pitch = 0.0;
        setVelocity(0.00000001);
    }
    
    setAddAngle(pitch);
    float velocityz= (pitch*4*M_PI_F)/180;
    
    double i=0.0;
    for(auto e : wheels){
        e->update(r, isPaused, i);
        i++;
    }
    
    
    //Setting the players new coordiantes and rotate him accordingly
    setComAngle(getComAngle()+velocityz);
    setRotAngle(velocityz);
    
    std::cout << "Com Angle: " << comAngle << " rot Angle: " << rotAngle << std::endl;
    
    setRotation(velocityz);
    
    if (hasCollision()){
        setCollision(false);
    } else {
        setX(getX()-getVelocity()*sinf(getComAngle()));
        setZ(getZ()-getVelocity()*cosf(getComAngle()));
    }
    
    emitterObj->update(r,isPaused,deltaTime);
}

