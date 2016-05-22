#include "Game.hpp"

void Game::startRun() {
  mainCamera->setPosition(cameraOffset);
  mainCamera->setRotation(vmml::Vector3f(-0.5f, 0.0f, 0.f));

  if (validMap) {
    bRenderer::log("START");
    std::shared_ptr<Marker> start = markers.back();
    player.setX(start->getX());
    player.setZ(start->getZ());
    bRenderer::log("POS z:" + std::to_string(player.getZ()) + " x:" +
                   std::to_string(player.getX()));
    player.setComAngle(start->angle);
    mainCamera->rotateCamera(0.0f, start->angle + M_PI, 0.0f);
  } else {
    bRenderer::log("ERROR::NOT A VALID MAP");
  }

  time = 0.0 - countdown;
  running = true;
  isPaused = true;
}

/* Draw your scene here */
void Game::loopFunction(const double &deltaTime, const double &elapsedTime) {
  if (running) {
    /// Draw scene ///
    bRenderer().getModelRenderer()->drawQueue(/*GL_LINES*/);
    bRenderer().getModelRenderer()->clearQueue();

    /// Update render queue ///
    updateRenderQueue("camera", deltaTime);

    if (DEBUG && time > 100.0) {  // return to menu
      bRenderer().stopRenderer();
      runCompleteCallbackFunc();
    }
  } else {
    bRenderer().stopRenderer();  // bRenderer just doesn't want to stop :o
  }

  // Quit renderer when escape is pressed ///
  if (bRenderer().getInput()->getKeyState(bRenderer::KEY_ESCAPE) ==
      bRenderer::INPUT_PRESS)
    bRenderer().terminateRenderer();
}

/* Update render queue */
void Game::updateRenderQueue(const std::string &camera,
                             const double &deltaTime) {
  updateTime(deltaTime);
  if (DEBUG) {
    handleDebuggingInput(camera);
  }

  vmml::Matrix4f modelMatrix;

  player.update(bRenderer(), isPaused, deltaTime);
  recordPosition();
  updateCamera(camera, deltaTime);

  for (auto e : ent) {
    if (collisionHandler.testOBBOverlap(player, *e)) {
      std::cout << "COLLISION" << std::endl;
      player.setCollision(true);
    }
    if (std::abs(player.getX() - e->getX()) < 40 ||
        std::abs(player.getZ() - e->getZ()) < 40) {
      e->draw(bRenderer(), modelMatrix);
    }
  }

  bool allCheckpoints = true;
  for (auto m : markers) {
    if (m->markerType == CHECKPOINT) {
      if (!m->passed) {
        allCheckpoints = false;
      }
    }
    if (collisionHandler.testOBBOverlap(player, *m)) {
      if (m->markerType == START && allCheckpoints) {
        // reached start again, stop run & return to menu
        bRenderer().stopRenderer();
        runCompleteCallbackFunc();
      }
    }
  }

  for (auto s : globalShaders) {
    s->setUniform("fogColor", this->fogColor);
  }

  // draw stuff
  player.draw(bRenderer(), modelMatrix);

  char timeBuffer[5];
  if (time < 0.0) {
    // render countdown
    sprintf(timeBuffer, "%.0f...", fabs(time));

    countdownText->setText(timeBuffer);
    bRenderer().getModelRenderer()->drawText(
        "countdown", camera,
        modelMatrix *
            vmml::create_translation(vmml::Vector3f(
                player.getX() + 5, player.getY() + 4, player.getZ() - 2)) *
            vmml::create_rotation(
                M_PI_F + player.getAddAngle() + player.getComAngle(),
                vmml::Vector3f::UNIT_Y) *
            vmml::create_scaling(vmml::Vector3f(2.0f)),
        std::vector<std::string>({}));
  } else {
    if (time < 1.0) {
      isPaused = false;
      countdownText->setText("GO!");
      bRenderer().getModelRenderer()->drawText(
          "countdown", camera,
          modelMatrix *
              vmml::create_translation(vmml::Vector3f(
                  player.getX() + 5, player.getY() + 4, player.getZ() - 2)) *
              vmml::create_rotation(
                  M_PI_F + player.getAddAngle() + player.getComAngle(),
                  vmml::Vector3f::UNIT_Y) *
              vmml::create_scaling(vmml::Vector3f(2.0f)),
          std::vector<std::string>({}));
    }
    sprintf(timeBuffer, "%.3fs", time);
    timeText->setText(timeBuffer);

    bRenderer().getModelRenderer()->drawText(
        "time", camera,
        modelMatrix *
            vmml::create_translation(vmml::Vector3f(
                player.getX(), player.getY() + 10, player.getZ() - 2)) *
            vmml::create_rotation(
                M_PI_F + player.getAddAngle() + player.getComAngle(),
                vmml::Vector3f::UNIT_Y) *
            vmml::create_scaling(vmml::Vector3f(1.0f)),
        std::vector<std::string>({}));
  }

  bRenderer().getModelRenderer()->queueModelInstance(
      "terrain", "terrain_instance", camera,
      modelMatrix * vmml::create_scaling(vmml::Vector3f(4.0f)),
      std::vector<std::string>({}));
  bRenderer().getModelRenderer()->queueModelInstance(
      "sphere", "sphere_instance", camera,
      modelMatrix * vmml::create_scaling(vmml::Vector3f(400.0f)),
      std::vector<std::string>({}));
}

/* Camera movement */
void Game::updateCamera(const std::string &camera, const double &deltaTime) {
  float camdistx = std::abs(player.getVelocity()) / player.getVelocity() *
                   (std::abs(player.getVelocity()) * 4) *
                   sinf(player.getComAngle());
  float camdisty = std::abs(player.getVelocity()) / player.getVelocity() *
                   (std::abs(player.getVelocity()) * 4) *
                   cosf(player.getComAngle());

  float height = -10.0f;
  if (isBirdsEye) {
    height = -70.0f;
  }

  vmml::Vector3f cameraPosition = vmml::Vector3f(
      -player.getX() - 17.0 * sinf(player.getComAngle()) - camdistx, height,
      -player.getZ() - 17.0 * cosf(player.getComAngle()) - camdisty);
  mainCamera->setPosition(cameraPosition);
  mainCamera->rotateCamera(0.0f, player.getRotAngle(), 0.0f);
}
