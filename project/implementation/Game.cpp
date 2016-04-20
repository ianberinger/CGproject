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
    
    //// Camera Movement ////
    updateCamera("camera", deltaTime);
    
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
    vmml::Matrix4f modelMatrix = vmml::create_translation(vmml::Vector3f(0.0f, 0.0f, 5.5f)) * vmml::create_scaling(vmml::Vector3f(0.8f));
   // vmml::Matrix4f rotationMatrix = vmml::create_rotation(rotation, vmml::Vector3f::UNIT_Y);
   // modelMatrix *= rotationMatrix;
    // submit to render queue
    bRenderer().getModelRenderer()->queueModelInstance("guy", "guy_instance", camera, modelMatrix, std::vector<std::string>({ }));
    
    bRenderer().getModelRenderer()->queueModelInstance("terrain", "terrain_instance", camera, modelMatrix, std::vector<std::string>({ }));
    bRenderer().getModelRenderer()->queueModelInstance("tree", "tree_instance", camera, modelMatrix*vmml::create_translation(vmml::Vector3f(5.0f,0.0f,5.0f))*vmml::create_scaling(vmml::Vector3f(0.02f,0.02f,0.02f)), std::vector<std::string>({ }));

    
}

/* Camera movement */
void Game::updateCamera(const std::string &camera, const double &deltaTime)
{
}

