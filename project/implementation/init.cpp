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
    
    float off[3]={0.0f,-5.0f,-18.0f};
    player.setOffSetCam(off);
    
    // set shader versions (optional)
    bRenderer().getObjects()->setShaderVersionDesktop("#version 120");
    bRenderer().getObjects()->setShaderVersionES("#version 100");
    
    // load materials and shaders before loading the model
    ShaderPtr guyShader = bRenderer().getObjects()->loadShaderFile("guy", 0, false, true, true, false, false);				// load shader from file without lighting, the number of lights won't ever change during rendering (no variable number of lights)
    ShaderPtr terrainShader = bRenderer().getObjects()->loadShaderFile("terrain", 0, false, true, true, false, false);
    ShaderPtr sphereShader = bRenderer().getObjects()->loadShaderFile("sphere", 0, false, true, true, false, false);
    ShaderPtr treeShader = bRenderer().getObjects()->loadShaderFile("tree", 0, false, true, true, false, false);
    ShaderPtr cubeShader = bRenderer().getObjects()->loadShaderFile("cube", 0, false, true, true, false, false);
    ShaderPtr carShader = bRenderer().getObjects()->loadShaderFile("car", 0, false, false, false, false, false);
    ShaderPtr wheelShader = bRenderer().getObjects()->loadShaderFile("wheel", 0, false, false, false, false, false);

    
    // create additional properties for a model
    PropertiesPtr guyProperties = bRenderer().getObjects()->createProperties("guyProperties");
    PropertiesPtr terrainProperties = bRenderer().getObjects()->createProperties("terrainProperties");
    PropertiesPtr sphereProperties = bRenderer().getObjects()->createProperties("sphereProperties");
    PropertiesPtr treeProperties = bRenderer().getObjects()->createProperties("treeProperties");
    PropertiesPtr cubeProperties = bRenderer().getObjects()->createProperties("cubeProperties");
    PropertiesPtr carProperties = bRenderer().getObjects()->createProperties("carProperties");
    PropertiesPtr wheelProperties = bRenderer().getObjects()->createProperties("wheelProperties");


    
    // load model
    bRenderer().getObjects()->loadObjModel("guy.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("terrain.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("sphere.obj", true, true, false, 4, true, false);    
    bRenderer().getObjects()->loadObjModel("tree.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("cube.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("car.obj", false, true, carShader, carProperties);
    bRenderer().getObjects()->loadObjModel("wheel.obj", false, true, wheelShader, wheelProperties);
    
    
    
    // create camera
    bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.0f, player.getOffSetCam()[1], player.getOffSetCam()[2]), vmml::Vector3f(-0.5f, 0.0f, 0.f));
    bRenderer().getObjects()->getCamera("camera")->rotateCamera(0.0f, M_PI_F, 0.0f);
    
    
    //loading the the map
    std::string currLine;
    std::ifstream file (bRenderer::getFilePath("map2.txt"));
    int count=0;
    int matr[50][50];
    if (file.is_open())
    {
        while ( getline (file,currLine) )
        {
            for(int i=0;i<currLine.length();i++){
                matr[count][i]=currLine[i]-'0';

            }
            count++;
        }
        file.close();
    }else{

    }
    
    for(int i=0; i<50;i++){
        for(int j=0;j<50;j++){
            if(matr[i][j]==2){
                std::shared_ptr<Entity> p( new Barrier((i*4-100),0,(j*4-100),1,1,1,true) );
                ent.push_back(p);
            } else if (matr[i][j]==5){
                bRenderer::log("START");
                player.setZ(i*4-100);
                player.setX(j*4-100);
            }
        }
    
    }
    
    
    
    // load materials and shaders before loading the model
    // Update render queue
    updateRenderQueue("camera", 0.0f);
}

/* This function is executed when terminating the renderer */
void Game::terminateFunction()
{
    bRenderer::log("I totally terminated this Renderer :-)");
}

