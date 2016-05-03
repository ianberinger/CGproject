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
    ShaderPtr rampShader = bRenderer().getObjects()->loadShaderFile("ramp", 0, false, false, false, false, false);


    globalShaders.push_back(sphereShader);
    globalShaders.push_back(terrainShader);
    
    // create additional properties for a model
    PropertiesPtr guyProperties = bRenderer().getObjects()->createProperties("guyProperties");
    PropertiesPtr terrainProperties = bRenderer().getObjects()->createProperties("terrainProperties");
    PropertiesPtr sphereProperties = bRenderer().getObjects()->createProperties("sphereProperties");
    PropertiesPtr treeProperties = bRenderer().getObjects()->createProperties("treeProperties");
    PropertiesPtr cubeProperties = bRenderer().getObjects()->createProperties("cubeProperties");
    PropertiesPtr carProperties = bRenderer().getObjects()->createProperties("carProperties");
    PropertiesPtr wheelProperties = bRenderer().getObjects()->createProperties("wheelProperties");
    PropertiesPtr rampProperties = bRenderer().getObjects()->createProperties("rampProperties");
    
    // load model
    bRenderer().getObjects()->loadObjModel("guy.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("terrain.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("sphere.obj", true, true, false, 4, true, false);    
    bRenderer().getObjects()->loadObjModel("tree.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("cube.obj", true, true, false, 4, true, false);
    bRenderer().getObjects()->loadObjModel("car.obj", false, true, carShader, carProperties);
    bRenderer().getObjects()->loadObjModel("wheel.obj", false, true, wheelShader, wheelProperties);
    bRenderer().getObjects()->loadObjModel("ramp.obj", true, true, false, 4, true, false);
    
    // create camera
    bRenderer().getObjects()->createCamera("camera", vmml::Vector3f(0.0f, player.getOffSetCam()[1], player.getOffSetCam()[2]), vmml::Vector3f(-0.5f, 0.0f, 0.f));
    
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
    
    bool startDefined = false;
    for(int i=0; i<50;i++){
        for(int j=0;j<50;j++){
            switch (matr[i][j]) {
                case 1: {
                    if (!startDefined) {
                        int right = matr[i][j+1];
                        int rightright = matr[i][j+2];
                        int up = matr[i+1][j];
                        int upup = matr[i+2][j];
                        
                        int z, x;
                        float angle;
                        // pi/2 = 90°
                        if (right == 1 && rightright == 1) {
                            if (matr[i+1][j+1] == 1) {
                                // 111
                                // x1x
                                bRenderer::log("START hor-down");
                                x = i;
                                z = j+1;
                                angle = 3*M_PI/2;
                            } else if (matr[i-1][j+1] == 1) {
                                // x1x
                                // 111
                                bRenderer::log("START hor-up");
                                x = i;
                                z = j+1;
                                angle = M_PI/2;
                            }
                        } else if (up == 1 && upup == 1) {
                            if (matr[i+1][j+1] == 1) {
                                // 1x
                                // 11
                                // 1x
                                bRenderer::log("START vert-right");
                                x = i + 1;
                                z = j;
                                angle = M_PI;
                            } else if (matr[i+1][j-1] == 1){
                                // x1
                                // 11
                                // x1
                                bRenderer::log("START vert-left");
                                x = i + 1;
                                z = j;
                                angle = 0.0;
                            }
                        }
                        if (x != 0 || z != 0) {
                            bRenderer::log("START");
                             bRenderer::log("MAP z:" + std::to_string(z) + " x:" + std::to_string(x));
                            player.setX(x*4-100);
                            player.setZ(z*4-100);
                            bRenderer::log("WORLD z:" + std::to_string(player.getZ()) + " x:" + std::to_string(player.getX()));
                            player.setComAngle(angle);
                            bRenderer().getObjects()->getCamera("camera")->rotateCamera(0.0f, angle+M_PI, 0.0f);
                            player.setCollisionHandler(&collisionHandler);
                            startDefined = true;
                            break;
                        }
                    }
                    break;
                }
                case 4: {
                    std::shared_ptr<Entity> p( new Barrier((i*4-100),0,(j*4-100),1,1,1,true, Entity::Type::COLLIDABLE) );
                    ent.push_back(p);
                    break;
                }
                case 6: {
                    std::shared_ptr<Entity> p( new Ramp((i*4-100),0,(j*4-100),1,2,5,true, Entity::Type::RAMP));
                    ent.push_back(p);
                    break;
                }
                case 7: {
                    std::shared_ptr<Entity> p( new Tree((i*4-100),0,(j*4-100),1,1,1,true, Entity::Type::COLLIDABLE) );
                    ent.push_back(p);
                    break;
                }
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

