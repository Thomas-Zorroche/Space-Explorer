#include "engine/InputHandler.hpp"
#include "common.hpp"
#include "hud/Hud.hpp"
#include "game/Game.hpp"

#include <iostream>
#include "GLFW/glfw3.h"

void InputHandler::ProcessInput(GLFWwindow* window, const std::shared_ptr<Camera>& camera, float deltaTime, 
    CollisionManager& collisionManager, Game& game)
{
    // Close Window
    // ===================================================================================================
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (game.run())
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Sprint 
        // ===================================================================================================
        float boostSprint = 1.0f;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            boostSprint = 3.0f; 

        // ===================================================================================================
        Movement(window, camera, deltaTime * boostSprint, game);

        // Print Debug cBox Mode
        // ===================================================================================================
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && _ActiveKey != ActiveKey::C) 
        {
            collisionManager.debugMode();
            Hud::get().debugMode();
            _ActiveKey = ActiveKey::C;
        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && _ActiveKey == ActiveKey::C)
        {
            _ActiveKey = ActiveKey::NONE;
        }

        // Endgame Button - Land on the planet
        // ===================================================================================================
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && camera->isInOrbit()
            && _ActiveKey != ActiveKey::A) // Q Qwerty = A Azerty
        {
            game.setEndgame();
            camera->SetCanTurn(false);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            _ActiveKey = ActiveKey::A;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE && _ActiveKey == ActiveKey::A)
        {
            _ActiveKey = ActiveKey::NONE;
        }

        // Endgame Button - Land on the planet
        // ===================================================================================================
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && _ActiveKey != ActiveKey::H)
        {
            Hud::get().hideHintPanel();
            _ActiveKey = ActiveKey::H;
        }
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE && _ActiveKey == ActiveKey::H)
        {
            _ActiveKey = ActiveKey::NONE;
        }
    }

    // Level Window
    else
    {
        camera->SetCanTurn(false);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

}

void InputHandler::Movement(GLFWwindow* window, const std::shared_ptr<Camera>& camera, float deltaTime, Game& game) {
    // Avancer
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)        // W Qwerty = Z Azerty
    {
        game.spaceship()->speedUp();
        game.spaceship()->setDirection(DIRCAM::FRONT);
        camera->Move(deltaTime * game.spaceship()->instantSpeed(), DIRCAM::FRONT);
    }
    // Reculer
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)        // W Qwerty = Z Azerty
    {
        game.spaceship()->speedUp();
        game.spaceship()->setDirection(DIRCAM::BACK);
        camera->Move(deltaTime * game.spaceship()->instantSpeed(), DIRCAM::BACK);
    }
    else
    {
        game.spaceship()->decelerate();
        camera->Move(deltaTime * game.spaceship()->instantSpeed(), game.spaceship()->getDirection());
    }

    //else
    //{
    //    game.spaceship()->decelerate();
    //    camera->Move(deltaTime * game.spaceship()->instantSpeed(), DIRCAM::BACK);
    //}
    
    //else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)   // A Qwerty = Q Azerty
    //    camera->Move(deltaTime, DIRCAM::LEFT);
    //else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)   // D Qwerty = D Azerty
    //    camera->Move(-deltaTime, DIRCAM::LEFT);
}


void InputHandler::SetCallback(GLFWwindow* window, CallbackPtr& callbackPtr)
{
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowUserPointer(window, &callbackPtr);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    CallbackPtr* callbackPtr = (CallbackPtr*)glfwGetWindowUserPointer(window);
    auto camera = callbackPtr->_camera;

    if (camera->GetCanTurn())
    {
        float xoffset = xpos - camera->GetLastX();
        float yoffset = ypos - camera->GetLastY();
        camera->SetLastX(xpos);
        camera->SetLastY(ypos);

        xoffset *= camera->GetSensitivity();
        yoffset *= camera->GetSensitivity();

        camera->rotateLeft(xoffset);
        camera->rotateUp(yoffset);
    }
}



