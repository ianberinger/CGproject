#include "RenderProject.h"

/* Initialize the Project */
void RenderProject::init()
{
	bRenderer::loadConfigFile("config.json");	// load custom configurations replacing the default values in Configuration.cpp

	// let the renderer create an OpenGL context and the main window
	if(Input::isTouchDevice())
		bRenderer().initRenderer(true);										// full screen on iOS
	else
		bRenderer().initRenderer(1920, 1080, false, "The Cave - Demo");		// windowed mode on desktop
		//bRenderer().initRenderer(View::getScreenWidth(), View::getScreenHeight(), true);		// full screen using full width and height of the screen

	// start main loop 
	bRenderer().runRenderer();
}

/* This function is executed when initializing the renderer */
void RenderProject::initFunction()
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

/* Draw your scene here */
void RenderProject::loopFunction(const double &deltaTime, const double &elapsedTime)
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

/* This function is executed when terminating the renderer */
void RenderProject::terminateFunction()
{
	bRenderer::log("I totally terminated this Renderer :-)");
}

/* Update render queue */
void RenderProject::updateRenderQueue(const std::string &camera, const double &deltaTime)
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
void RenderProject::updateCamera(const std::string &camera, const double &deltaTime)
{
}

/* For iOS only: Handle device rotation */
void RenderProject::deviceRotated()
{
	if (bRenderer().isInitialized()){
		// set view to full screen after device rotation
		bRenderer().getView()->setFullscreen(true);
		bRenderer::log("Device rotated");
	}
}

/* For iOS only: Handle app going into background */
void RenderProject::appWillResignActive()
{
	if (bRenderer().isInitialized()){
		// stop the renderer when the app isn't active
		bRenderer().stopRenderer();
	}
}

/* For iOS only: Handle app coming back from background */
void RenderProject::appDidBecomeActive()
{
	if (bRenderer().isInitialized()){
		// run the renderer as soon as the app is active
		bRenderer().runRenderer();
	}
}

/* For iOS only: Handle app being terminated */
void RenderProject::appWillTerminate()
{
	if (bRenderer().isInitialized()){
		// terminate renderer before the app is closed
		bRenderer().terminateRenderer();
	}
}

/* Helper functions */
GLfloat RenderProject::randomNumber(GLfloat min, GLfloat max){
	return min + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (max - min)));
}