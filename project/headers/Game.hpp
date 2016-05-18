#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

#include "bRenderer.h"
#include "Player.hpp"
#include "Map.hpp"
#include "CollisionHandler.hpp"

struct positionInTime {
    float time;
    float comAngle;
    float addAngle;
    vmml::Vector3f position;
};

class Game : public IRenderProject
{
public:
    static map _map;
	/* Constructor and Destructor */
	Game() : IRenderProject(){}
    virtual ~Game(){bRenderer::log("game deleted");}

    /* Initialize the Project */
    void init();
    
	//// RenderProject functions ////

	/* This function is executed when initializing the renderer */
	void initFunction();

	/* Draw your scene here */
	void loopFunction(const double &deltaTime, const double &elapsedTime);

	/* This function is executed when terminating the renderer */
	void terminateFunction();
    
    
    //// gameControl for parent eg. ViewController ////
    
    void runCompleteCallback(void (*f)()){runCompleteCallbackFunc = f;}
    //void callback(void (*f)()){bRenderer().setTerminateFunction(f);};
    float getTime() {return time;}
    std::vector<positionInTime> getPositions() {return pastPositions;}
    void startRun();
    //void stop(){bRenderer().stopRenderer();}

	//// iOS specific ////

    /* For iOS only: Handle device rotation */
    void deviceRotated();
    
    /* For iOS only: Handle app going into background */
    void appWillResignActive();
    
    /* For iOS only: Handle app coming back from background */
    void appDidBecomeActive();
    
    /* For iOS only: Handle app being terminated */
    void appWillTerminate();
    
	/* Make renderer accessible to public so we can get the UIView on iOS */
    Renderer& getProjectRenderer()
    {
        return bRenderer();
    }
    
    bool DEBUG = false;
    
private:
    
	/* Update render queue */
	void updateRenderQueue(const std::string &camera, const double &deltaTime);

	/* Camera movement */
    void updateCamera(const std::string &camera, const double &deltaTime);
    
    void updateTime(const double &deltaTime){if(!isPaused||time<0.0){time+=deltaTime;}}
    void recordPosition(){if(!isPaused){pastPositions.push_back(positionInTime{time, player.getComAngle(), player.getAddAngle(), player.getXYZ()});}}
    
    /* Debugging */
    void handleDebuggingInput(const std::string &camera);
    void togglePause(){isPaused=!isPaused;}
    void toggleBirdsEye(){isBirdsEye=!isBirdsEye;}

    /* Constants */
    const vmml::Vector4f fogColor = vmml::Vector4f(0.5, 0.5, 0.5, 1);
	/* Variables */
	GLfloat _randomOffset;
	GLfloat _offset;
	GLfloat _cameraSpeed;
	double _mouseX, _mouseY;
    Player player;
    Collisionhandler collisionHandler;
    std::vector<ShaderPtr> globalShaders;
	GLint _lastStateSpaceKey = 0;
	vmml::Matrix4f _viewMatrixHUD;
    std::vector<std::shared_ptr<Entity>> ent;
    marker start;
    std::vector<marker> checkpoints;
    std::vector<positionInTime> pastPositions;
    const float countdown = 3.0;
    float time = 0.0;

    bool isPaused = true; // used for signaling a paused game, while still rendering
    bool isBirdsEye = false;
    bool running = false; // used for signaling that game isn't running at all (no rendering)
    void (*runCompleteCallbackFunc)();
};

#endif /* defined(PROJECT_MAIN_H) */
