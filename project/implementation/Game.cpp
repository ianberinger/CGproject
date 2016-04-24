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
    vmml::Matrix4f guyMatrix = moveCar(modelMatrix, deltaTime);
    updateCamera(camera, guyMatrix, deltaTime);
    //float fogCoefficent = 1.0 / (pow(M_E, (dist*0.05)));
    
    ShaderPtr guyShader = bRenderer().getObjects()->getShader("guy");
    ShaderPtr terrainShader = bRenderer().getObjects()->getShader("terrain");
    ShaderPtr cubeShader = bRenderer().getObjects()->getShader("cube");
    ShaderPtr treeShader = bRenderer().getObjects()->getShader("tree");
    
    // set fog color
    guyShader->setUniform("fogColor", this->fogColor);
    terrainShader->setUniform("fogColor", this->fogColor);
    cubeShader->setUniform("fogColor", this->fogColor);
    treeShader->setUniform("fogColor", this->fogColor);
    
    // draw stuff
    bRenderer().getModelRenderer()->drawModel("guy", "camera", guyMatrix, std::vector<std::string>({ }));
    bRenderer().getModelRenderer()->queueModelInstance("terrain", "terrain_instance", camera, modelMatrix, std::vector<std::string>({ }));
    bRenderer().getModelRenderer()->queueModelInstance("tree", "tree_instance", camera, modelMatrix*vmml::create_translation(vmml::Vector3f(5.0f,0.0f,5.0f))*vmml::create_scaling(vmml::Vector3f(0.02f,0.02f,0.02f)), std::vector<std::string>({ }));
    
    vmml::Vector3f playerPos = player.getXYZ();
    
    for(auto e: ent) {
        vmml::Vector3f v = vmml::Vector3f(e->getX(), e->getY(), e->getZ());
        float distance = playerPos.distance(v);
        if (distance < e->getWidth()) {
            player.setCollision(true);
            bRenderer::log("distance:" + std::to_string(distance));
        }
        if(std::abs(player.getX()-e->getX())<40||std::abs(player.getZ()-e->getZ())<40){
        bRenderer().getModelRenderer()->drawModel("cube", "camera", modelMatrix*vmml::create_translation(v), std::vector<std::string>({ }));
        }
    }

}

vmml::Matrix4f Game::moveCar(const vmml::Matrix4f &modelMatrix, const double &deltaTime) {
   
    //Getting the inputs from the gyro sensor
    float roll = bRenderer().getInput()->getGyroscopeRoll(); // tilt
    float pitch = bRenderer().getInput()->getGyroscopePitch(); // left / right
    bRenderer::log("roll:" + std::to_string(roll));
    bRenderer::log("pitch:" + std::to_string(pitch));
    
    float velocity = (roll+0.75)*2.5;
    float velocityz= (pitch*4*M_PI_F)/180;
    
    //Setting the players new coordiantes and rotate him accordingly
    player.setComAngle(player.getComAngle()+velocityz);
    player.setRotAngle(velocityz);
    
    if (!player.hasCollision()){
        player.setX(player.getX()-velocity*sinf(player.getComAngle()));
        player.setZ(player.getZ()-velocity*cosf(player.getComAngle()));
    } else {
        bRenderer::log("COLLISION");
        player.setCollision(false);
        
        if (velocity < 0.0) {
            player.setX(player.getX()-velocity*sinf(player.getComAngle()));
            player.setZ(player.getZ()-velocity*cosf(player.getComAngle()));
        }
    }
    
    
    vmml::Matrix4f transformationMatrix{modelMatrix};
    transformationMatrix *= vmml::create_translation(vmml::Vector3f(player.getX(),0.0,player.getZ()))*vmml::create_rotation(player.getComAngle(), vmml::Vector3f::UNIT_Y);
    
        return transformationMatrix;
}

/* Camera movement */
void Game::updateCamera(const std::string &camera, const vmml::Matrix4f &carMatrix, const double &deltaTime)
{
    CameraPtr cameraPtr = bRenderer().getObjects()->getCamera(camera);

    vmml::Vector3f cameraPosition = vmml::Vector3f(-player.getX()-20.0*sinf(player.getComAngle()), -5.0f, -player.getZ()-20.0*cosf(player.getComAngle()));
    cameraPtr->setPosition(cameraPosition);
    cameraPtr->rotateCamera(0.0f,player.getRotAngle(),0.0f);
}

