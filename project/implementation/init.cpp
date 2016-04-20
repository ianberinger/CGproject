#include "Game.h"
/* Initialize the Game */

void Game::init()
{
    bRenderer::loadConfigFile("config.json");	// load custom configurations replacing the default values in Configuration.cpp
    
    // let the renderer create an OpenGL context and the main window
    if(Input::isTouchDevice())
        bRenderer().initRenderer(true);										// full screen on iOS
    else
        bRenderer().initRenderer(1920, 1080, false, "Game on Desktop TODO");		// windowed mode on desktop
    //bRenderer().initRenderer(View::getScreenWidth(), View::getScreenHeight(), true);		// full screen using full width and height of the screen
    
    // start main loop
    bRenderer().runRenderer();
}

/* This function is executed when initializing the renderer */
void Game::initFunction()
{
    
    _offset = 0.0f;
    _randomOffset = 0.0f;
    _cameraSpeed = 40.0f;
    _running = true; _lastStateSpaceKey = bRenderer::INPUT_UNDEFINED;
    _viewMatrixHUD = Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);
    
    // set shader versions (optional)
    bRenderer().getObjects()->setShaderVersionDesktop("#version 120");
    bRenderer().getObjects()->setShaderVersionES("#version 100");
    
    // load materials and shaders before loading the model
    ShaderPtr guyShader = bRenderer().getObjects()->loadShaderFile("guy", 0, false, true, true, false, false);				// load shader from file without lighting, the number of lights won't ever change during rendering (no variable number of lights)
    ShaderPtr terrainShader = bRenderer().getObjects()->loadShaderFile("terrain", 0, false, true, true, false, false);
    ShaderPtr treeShader = bRenderer().getObjects()->loadShaderFile("tree", 0, false, true, true, false, false);
    
    
    // create additional properties for a model
    PropertiesPtr guyProperties = bRenderer().getObjects()->createProperties("guyProperties");
    PropertiesPtr terrainProperties = bRenderer().getObjects()->createProperties("guyProperties");
    PropertiesPtr treeProperties = bRenderer().getObjects()->createProperties("guyProperties");
    
    
    // load model
    bRenderer().getObjects()->loadObjModel("guy.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("terrain.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("tree.obj", true, true, false, 4, true, false);
    
    // automatically generates a shader with a maximum of 4 lights (number of lights may vary between 0 and 4 during rendering without performance loss)
    
    
    
    
    // create camera
    bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.0f, -3.0f, 0.5f), vmml::Vector3f(0.f, 0.0f, 0.f));
    
    
    
    
    
    
    
    // load materials and shaders before loading the model
    // Update render queue
    updateRenderQueue("camera", 0.0f);
}

/* This function is executed when terminating the renderer */
void Game::terminateFunction()
{
    bRenderer::log("I totally terminated this Renderer :-)");
}

