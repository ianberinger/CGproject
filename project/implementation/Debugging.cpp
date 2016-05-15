//
//  Debugging.cpp
//  bRenderer_ios
//
//  Created by Ian Beringer on 5/9/16.
//
//

#include "Game.h"

void Game::handleDebuggingInput(const std::string &camera)
{
    if (bRenderer().getInput()->doubleTapRecognized()) {
        bRenderer::log("DOUBLE");
        toggleBirdsEye();
        CameraPtr cameraPtr = bRenderer().getObjects()->getCamera(camera);
        if (isBirdsEye) {
            cameraPtr->rotateCamera(M_PI*0.25,0.0f,0.0f);
        } else {
            cameraPtr->rotateCamera(M_PI*1.75,0.0f,0.0f);
        }
        
    } else if (bRenderer().getInput()->singleTapRecognized()) {
        bRenderer::log("SINGLE");
        togglePause();
    }
}