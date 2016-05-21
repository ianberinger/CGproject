#include "Game.hpp"

void Game::handleDebuggingInput(const std::string &camera) {
  if (bRenderer().getInput()->doubleTapRecognized()) {
    bRenderer::log("DOUBLE");
    toggleBirdsEye();
    if (isBirdsEye) {
      mainCamera->rotateCamera(M_PI * 0.25, 0.0f, 0.0f);
    } else {
      mainCamera->rotateCamera(M_PI * 1.75, 0.0f, 0.0f);
    }

  } else if (bRenderer().getInput()->singleTapRecognized()) {
    bRenderer::log("SINGLE");
    togglePause();
  }
}