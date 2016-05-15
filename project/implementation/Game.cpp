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
    handleDebuggingInput(camera);
    
    vmml::Matrix4f modelMatrix;
    
    player.update(bRenderer(), isPaused);
    updateCamera(camera, deltaTime);
    
    for(auto e: ent) {
        if (collisionHandler.testAABBOverlap(player, *e)) {
            player.setCollision(true);
        }
        if(std::abs(player.getX()-e->getX())<40||std::abs(player.getZ()-e->getZ())<40){
            e->draw(bRenderer(),modelMatrix);
        }
    }
    
    for (auto s: globalShaders) {
        s->setUniform("fogColor", this->fogColor);
    }
    
    // draw stuff
    player.draw(bRenderer(),modelMatrix);
    
    
    if (countdown > 0.0) {
        // render countdown
        char buffer [5];
        sprintf(buffer, "%.0f...", countdown);
        
        bRenderer().getObjects()->getTextSprite("countdown")->setText(buffer);
        bRenderer().getModelRenderer()->drawText("countdown", camera, modelMatrix*vmml::create_translation(vmml::Vector3f(player.getX()+5, player.getY()+4, player.getZ()-2))*vmml::create_rotation(M_PI_F+player.getAddAngle()+player.getComAngle(), vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(2.0f)), std::vector<std::string>({ }));
        countdown -= deltaTime;
    } else if (countdown > -1.0) {
        countdown -= deltaTime;
        isPaused = false;
        bRenderer().getObjects()->getTextSprite("countdown")->setText("GO!");
        bRenderer().getModelRenderer()->drawText("countdown", camera, modelMatrix*vmml::create_translation(vmml::Vector3f(player.getX()+5, player.getY()+4, player.getZ()-2))*vmml::create_rotation(M_PI_F+player.getAddAngle()+player.getComAngle(), vmml::Vector3f::UNIT_Y)*vmml::create_scaling(vmml::Vector3f(2.0f)), std::vector<std::string>({ }));
    }

    bRenderer().getModelRenderer()->queueModelInstance("terrain", "terrain_instance", camera, modelMatrix*vmml::create_scaling(vmml::Vector3f(2.0f)), std::vector<std::string>({ }));
    bRenderer().getModelRenderer()->queueModelInstance("sphere", "sphere_instance", camera, modelMatrix*vmml::create_scaling(vmml::Vector3f(200.0f)), std::vector<std::string>({ }));
}


/* Camera movement */
void Game::updateCamera(const std::string &camera, const double &deltaTime)
{
    CameraPtr cameraPtr = bRenderer().getObjects()->getCamera(camera);
    
    float camdistx=std::abs(player.getVelocity())/player.getVelocity()*(std::abs(player.getVelocity())*4)*sinf(player.getComAngle());
    float camdisty=std::abs(player.getVelocity())/player.getVelocity()*(std::abs(player.getVelocity())*4)*cosf(player.getComAngle());

    float height = -10.0f;
    if (isBirdsEye) {
        height = -70.0f;
    }
    
    vmml::Vector3f cameraPosition = vmml::Vector3f(-player.getX()-17.0*sinf(player.getComAngle())-camdistx, height, -player.getZ()-17.0*cosf(player.getComAngle())-camdisty);
    cameraPtr->setPosition(cameraPosition);
    cameraPtr->rotateCamera(0.0f,player.getRotAngle(),0.0f);
}

