#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

#include "CollisionHandler.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "bRenderer.h"

struct positionInTime {
  float time;
  float comAngle;
  float addAngle;
  vmml::Vector3f position;
};

class Game : public IRenderProject {
 public:
  static map _map;
  /* Constructor and Destructor */
  Game() : IRenderProject() {}
  virtual ~Game() { bRenderer::log("game deleted"); }

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
  void runCompleteCallback(void (*f)()) { runCompleteCallbackFunc = f; }
  float getTime() { return time; }
  void startRun();
  // std::vector<positionInTime> getPositions() { return currentRun; }
  // void callback(void (*f)()){bRenderer().setTerminateFunction(f);};
  // void stop(){bRenderer().stopRenderer();}

  //// iOS specific ////
  void deviceRotated();
  void appWillResignActive();
  void appDidBecomeActive();
  void appWillTerminate();

  /* Make renderer accessible to public so we can get the UIView on iOS */
  Renderer &getProjectRenderer() { return bRenderer(); }

  // Variables set by parent //
  bool DEBUG = false;
  bool COMPETE = false;

 private:
  /* Update render queue */
  void updateRenderQueue(const std::string &camera, const double &deltaTime);
  void drawText(const std::string &camera, vmml::Matrix4f &modelMatrix);

  /* Camera movement */
  void updateCamera(const std::string &camera, const double &deltaTime);

  /* Game state */
  void updateTime(const double &deltaTime) {
    if (!isPaused || time < 0.0) {
      time += deltaTime;
    } else if (runComplete) {
      exitCounter += deltaTime;
    }
  }
  void recordPosition() {
    if (!isPaused) {
      currentRun.push_back(positionInTime{
          time, player.getComAngle(), player.getAddAngle(), player.getXYZ()});
    }
  }

  /* Debugging */
  void handleDebuggingInput(const std::string &camera);
  void togglePause() { isPaused = !isPaused; }
  void toggleBirdsEye() { isBirdsEye = !isBirdsEye; }

  /* Constants */
  const float countdown = 3.0;
  const vmml::Vector4f fogColor = vmml::Vector4f(0.5, 0.5, 0.5, 1);
  const vmml::Vector3f cameraOffset = vmml::Vector3f(0.0f, -5.0f, -18.0f);

  // const GLfloat _randomOffset = 0.0f;
  // const GLfloat _offset = 0.0f;
  // const GLfloat _cameraSpeed = 40.0f;
  // const vmml::Matrix4f _viewMatrixHUD = Camera::lookAt(vmml::Vector3f(0.0f,
  // 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);

  /* Variables */
  bool validMap =
      false;  // signifies a valid map, ie. valid start and checkpoints
  bool runComplete;
  bool hitCheckpoint = false;
  std::vector<std::shared_ptr<Marker>> markers;
  std::vector<positionInTime> currentRun;
  std::vector<positionInTime> lastRun;

  Player player = Player(false);
  Player ghost = Player(true);
  CameraPtr mainCamera;
  TextSpritePtr centerText;
  TextSpritePtr topText;
  std::vector<std::shared_ptr<Entity>> ent;

  Collisionhandler collisionHandler;
  void (*runCompleteCallbackFunc)();
  std::vector<ShaderPtr> globalShaders;

  float time;
  float exitCounter;
  bool isPaused =
      true;  // used for signaling a paused game, while still rendering
  bool isBirdsEye = false;
  bool running = false;  // used for signaling that game isn't running at all
                         // (no rendering)

  // double _mouseX, _mouseY;
  // GLint _lastStateSpaceKey = bRenderer::INPUT_UNDEFINED;
};

#endif /* defined(PROJECT_MAIN_H) */
