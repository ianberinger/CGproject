#include "Game.h"


/* Draw your scene here */
void Game::loopFunction(const double &deltaTime, const double &elapsedTime)
{
    /// Draw scene ///
    bRenderer().getModelRenderer()->drawQueue(/*GL_LINES*/);
    bRenderer().getModelRenderer()->clearQueue();
    
    /// Update render queue ///
    updateRenderQueue("camera", deltaTime);
    
    // Quit renderer when escape is pressed ///
    if (bRenderer().getInput()->getKeyState(bRenderer::KEY_ESCAPE) == bRenderer::INPUT_PRESS)
        bRenderer().terminateRenderer();
}

/* Update render queue */
void Game::updateRenderQueue(const std::string &camera, const double &deltaTime)
{
    vmml::Matrix4f modelMatrix;
    moveCar(modelMatrix, deltaTime);
    updateCamera(camera, deltaTime);
    
    vmml::Vector3f playerPos = player.getXYZ();
    
    for(auto e: ent) {
        vmml::Vector3f v = vmml::Vector3f(e->getX(), e->getY(), e->getZ());
        float distance = playerPos.distance(v);
        if (collisionHandler.testAABBOverlap(player, *e)) {
            player.setCollision(true);
            bRenderer::log("distance:" + std::to_string(distance));
        }
        if(std::abs(player.getX()-e->getX())<40||std::abs(player.getZ()-e->getZ())<40){
            e->draw(bRenderer(),modelMatrix);
        }
    }
    
    
    
    ShaderPtr terrainShader = bRenderer().getObjects()->getShader("terrain");
    ShaderPtr treeShader = bRenderer().getObjects()->getShader("tree");
    
    // set fog color
    terrainShader->setUniform("fogColor", this->fogColor);
    treeShader->setUniform("fogColor", this->fogColor);

    
    // draw stuff
    player.draw(bRenderer(),modelMatrix);
    
    
    bRenderer().getModelRenderer()->queueModelInstance("terrain", "terrain_instance", camera, modelMatrix, std::vector<std::string>({ }));
    bRenderer().getModelRenderer()->queueModelInstance("tree", "tree_instance", camera, modelMatrix*vmml::create_translation(vmml::Vector3f(5.0f,0.0f,5.0f))*vmml::create_scaling(vmml::Vector3f(0.02f,0.02f,0.02f)), std::vector<std::string>({ }));

}

void Game::moveCar(const vmml::Matrix4f &modelMatrix, const double &deltaTime) {
   
    //Getting the inputs from the gyro sensor
    float roll = bRenderer().getInput()->getGyroscopeRoll(); // tilt
    float pitch = bRenderer().getInput()->getGyroscopePitch(); // left / right
    bRenderer::log("roll:" + std::to_string(roll));
    bRenderer::log("pitch:" + std::to_string(pitch));
    
    player.setVelocity((roll+0.75)*2.5);
    float velocityz= (pitch*4*M_PI_F)/180;
    
    //Setting the players new coordiantes and rotate him accordingly
    player.setComAngle(player.getComAngle()+velocityz);
    player.setRotAngle(velocityz);
    
    if (!player.hasCollision()){
        player.setX(player.getX()-player.getVelocity()*sinf(player.getComAngle()));
        player.setZ(player.getZ()-player.getVelocity()*cosf(player.getComAngle()));
    } else {
        bRenderer::log("COLLISION");
        player.setCollision(false);
        
        if (player.getVelocity() < 0.0) {
            player.setX(player.getX()-player.getVelocity()*sinf(player.getComAngle()));
            player.setZ(player.getZ()-player.getVelocity()*cosf(player.getComAngle()));
        }
    }
    
}

/* Camera movement */
void Game::updateCamera(const std::string &camera, const double &deltaTime)
{
    CameraPtr cameraPtr = bRenderer().getObjects()->getCamera(camera);
    
    float camdistx=std::abs(player.getVelocity())/player.getVelocity()*(std::abs(player.getVelocity())*2.5)*sinf(player.getComAngle());
    float camdisty=std::abs(player.getVelocity())/player.getVelocity()*(std::abs(player.getVelocity())*2.5)*cosf(player.getComAngle());

    vmml::Vector3f cameraPosition = vmml::Vector3f(-player.getX()-17.0*sinf(player.getComAngle())-camdistx, -5.0f, -player.getZ()-17.0*cosf(player.getComAngle())-camdisty);
    cameraPtr->setPosition(cameraPosition);
    cameraPtr->rotateCamera(0.0f,player.getRotAngle(),0.0f);
}

