#include "Game.h"


/* Draw your scene here */
void Game::loopFunction(const double &deltaTime, const double &elapsedTime)
{
//	bRenderer::log("FPS: " + std::to_string(1 / deltaTime));	// write number of frames per second to the console every frame

	//// Draw Scene and do post processing ////

	/// Begin post processing ///


    /// Draw scene ///
    
    bRenderer().getModelRenderer()->drawQueue(/*GL_LINES*/);
    bRenderer().getModelRenderer()->clearQueue();
    
    /// Update render queue ///
    updateRenderQueue("camera", deltaTime);
    
    // Quit renderer when escape is pressed
    if (bRenderer().getInput()->getKeyState(bRenderer::KEY_ESCAPE) == bRenderer::INPUT_PRESS)
        bRenderer().terminateRenderer();

}

/* Update render queue */
void Game::updateRenderQueue(const std::string &camera, const double &deltaTime)
{

    /*** Guy ***/
    // get input rotation
    
    TouchMap touchMap = bRenderer().getInput()->getTouches();
    int i = 0;
    float rotation = 0.0f;
    for (auto t = touchMap.begin(); t != touchMap.end(); ++t)
    {
        Touch touch = t->second;
        rotation = (touch.currentPositionX - touch.startPositionX) / 100;
        if (++i > 1)
            break;
    }
    bRenderer().getObjects()->getCamera("camera")->moveCameraForward(rotation);
    
    // translate and scale
    vmml::Matrix4f modelMatrix = vmml::create_translation(vmml::Vector3f(0.0f, 0.0f, 5.5f));
   // vmml::Matrix4f rotationMatrix = vmml::create_rotation(rotation, vmml::Vector3f::UNIT_Y);
   // modelMatrix *= rotationMatrix;
    // submit to render queue
    vmml::Vector4f eyePos(bRenderer().getObjects()->getCamera("camera")->getPosition(),0);

    vmml::Matrix4f guyMatrix = moveCar(modelMatrix, deltaTime);
    updateCamera(camera, guyMatrix, deltaTime);
    
    ShaderPtr guyShader = bRenderer().getObjects()->getShader("guy");
    //guyShader->setUniform("ModelViewMatrix", guyMatrix);
    guyShader->setUniform("EyePos", eyePos);
    
    
    bRenderer().getModelRenderer()->drawModel("guy", "camera", guyMatrix, std::vector<std::string>({ }));
    
    
    ShaderPtr terrainShader = bRenderer().getObjects()->getShader("terrain");
    guyShader->setUniform("EyePos", eyePos);

    ShaderPtr cubeShader = bRenderer().getObjects()->getShader("cube");
    guyShader->setUniform("EyePos", eyePos);
    
    
    ShaderPtr treeShader = bRenderer().getObjects()->getShader("tree");
    guyShader->setUniform("EyePos", eyePos);
    

    bRenderer().getModelRenderer()->queueModelInstance("terrain", "terrain_instance", camera, modelMatrix, std::vector<std::string>({ }));
    bRenderer().getModelRenderer()->queueModelInstance("tree", "tree_instance", camera, modelMatrix*vmml::create_translation(vmml::Vector3f(5.0f,0.0f,5.0f))*vmml::create_scaling(vmml::Vector3f(0.02f,0.02f,0.02f)), std::vector<std::string>({ }));
    
    for(int i=0; i<ent.size();i++){
        float a= ent[i]->getX();
        float b= ent[i]->getY();
        float c= ent[i]->getZ();

        bRenderer().getModelRenderer()->drawModel("cube", "camera", modelMatrix*vmml::create_translation(vmml::Vector3f(a,b,c)), std::vector<std::string>({ }));
    }
    
}

vmml::Matrix4f Game::moveCar(const vmml::Matrix4f &modelMatrix, const double &deltaTime) {
    float roll = bRenderer().getInput()->getGyroscopeRoll();
    float pitch = bRenderer().getInput()->getGyroscopePitch();
    float velocity = (roll+0.75)*2.5;
    float velocityz= pitch*2.5;

    _carPosition = _carPosition+vmml::Vector3f(velocityz, 0.0f, velocity);
    vmml::Matrix4f transformationMatrix{modelMatrix};
    transformationMatrix *= vmml::create_translation(vmml::Vector3f(-_carPosition.x(),0.0,(-_carPosition.z())));
    
    
    _carPosition = _carPosition+vmml::Vector3f(velocityz, 0.0f, velocity);
    return transformationMatrix;
}

/* Camera movement */
void Game::updateCamera(const std::string &camera, const vmml::Matrix4f &carMatrix, const double &deltaTime)
{
    CameraPtr cameraPtr = bRenderer().getObjects()->getCamera(camera);
    float roll = bRenderer().getInput()->getGyroscopeRoll(); // tilt
    float pitch = bRenderer().getInput()->getGyroscopePitch(); // left / right
    bRenderer::log("roll:" + std::to_string(roll));
    bRenderer::log("pitch:" + std::to_string(pitch));
    
    vmml::Vector3f cameraPosition = vmml::Vector3f(_carPosition.x(), -5.0f, _carPosition.z()-20.0);
    cameraPtr->setPosition(cameraPosition);
    
    /*cameraPtr->rotateCamera(0.0f, pitch / 50.0, 0.0f);
    cameraPtr->moveCameraForward(roll * 50);*/
}

