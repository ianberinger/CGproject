#include "Game.hpp"

int Game::_map[50][50] = {0};
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
}

/* This function is executed when initializing the renderer */
void Game::initFunction()
{
    // set shader versions (optional)
    bRenderer().getObjects()->setShaderVersionDesktop("#version 120");
    bRenderer().getObjects()->setShaderVersionES("#version 100");
    
    // load materials and shaders before loading the model
    ShaderPtr guyShader = bRenderer().getObjects()->loadShaderFile("guy", 0, false, true, true, false, false);				// load shader from file without lighting, the number of lights won't ever change during rendering (no variable number of lights)
    ShaderPtr terrainShader = bRenderer().getObjects()->loadShaderFile("terrain", 0, false, true, true, false, false);
    ShaderPtr sphereShader = bRenderer().getObjects()->loadShaderFile("sphere", 0, false, true, true, false, false);
    ShaderPtr treeShader = bRenderer().getObjects()->loadShaderFile("tree", 0, false, true, true, false, false);
    ShaderPtr barrierShader = bRenderer().getObjects()->loadShaderFile("barrier", 0, false, true, true, false, false);
    ShaderPtr carShader = bRenderer().getObjects()->loadShaderFile("car", 0, false, false, false, false, false);
    ShaderPtr wheelShader = bRenderer().getObjects()->loadShaderFile("wheel", 0, false, false, false, false, false);
    ShaderPtr rampShader = bRenderer().getObjects()->loadShaderFile("ramp", 0, false, false, false, false, false);
    ShaderPtr particlesShader = bRenderer().getObjects()->loadShaderFile("particles", 0, false, false, false, false, false);
    ShaderPtr roadShader = bRenderer().getObjects()->loadShaderFile("road", 0, false, true, true, false, false);

    globalShaders.push_back(sphereShader);
    globalShaders.push_back(terrainShader);
    
    // create additional properties for a model
    PropertiesPtr guyProperties = bRenderer().getObjects()->createProperties("guyProperties");
    PropertiesPtr terrainProperties = bRenderer().getObjects()->createProperties("terrainProperties");
    PropertiesPtr sphereProperties = bRenderer().getObjects()->createProperties("sphereProperties");
    PropertiesPtr treeProperties = bRenderer().getObjects()->createProperties("treeProperties");
    PropertiesPtr barrierProperties = bRenderer().getObjects()->createProperties("barrierProperties");
    PropertiesPtr carProperties = bRenderer().getObjects()->createProperties("carProperties");
    PropertiesPtr wheelProperties = bRenderer().getObjects()->createProperties("wheelProperties");
    PropertiesPtr rampProperties = bRenderer().getObjects()->createProperties("rampProperties");
    PropertiesPtr roadProperties = bRenderer().getObjects()->createProperties("roadProperties");
    
    // load models
    bRenderer().getObjects()->loadObjModel("guy.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("terrain.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("sphere.obj", true, true, false, 4, true, false);    
    bRenderer().getObjects()->loadObjModel("tree.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("barrier.obj", false, true, barrierShader, barrierProperties);
    bRenderer().getObjects()->loadObjModel("car.obj", false, true, carShader, carProperties);
    bRenderer().getObjects()->loadObjModel("wheel.obj", false, true, wheelShader, wheelProperties);
    bRenderer().getObjects()->loadObjModel("ramp.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("Plate.obj", false, true, roadShader, roadProperties);
    
    // load fonts
    FontPtr comicSans = bRenderer().getObjects()->loadFont("Comic Sans MS.ttf", 500);
    
    // create text sprites
    bRenderer().getObjects()->createTextSprite("countdown", vmml::Vector3f(1.0, 1.0, 1.0), "UNSET", comicSans);
    bRenderer().getObjects()->createTextSprite("time", vmml::Vector3f(1.0, 1.0, 1.0), "UNSET", comicSans);

    // create camera
    bRenderer().getObjects()->createCamera("camera");
    
    //loading the the map
    start = loadMap(bRenderer::getFilePath("map2.txt"), _map, ent, checkpoints);
    
    player.setCollisionHandler(&collisionHandler);
}

/* This function is executed when terminating the renderer */
void Game::terminateFunction() { bRenderer::log("I totally terminated this Renderer :-)");}