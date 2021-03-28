#include "engine/Application.hpp"
#include "engine/Renderer.hpp"
#include "engine/Camera.hpp"
#include "engine/Scene.hpp"
#include "engine/InputHandler.hpp"
#include "engine/ResourceManager.hpp"

#include "collision/CollisionManager.hpp"

#include "game/Game.hpp"
#include "game/InteractiveObject.hpp"

#include "hud/Hud.hpp"

#include <cstdlib>  // for rand(), srand()
#include <ctime>    // for time()


void mainloop(Window& windowObject)
{
    GLFWwindow* window = windowObject.WindowPtr();

    srand(time(0));

    // Initialisation Collision Manager
    CollisionManager collisionManager;
    StaticMesh::SetCollisionManagerPtr(&collisionManager);

    // Load all the 
    ResourceManager::Get().LoadAllShaders();

    Scene scene;
    Game game;
    
    Hud::get().init(window);

    InteractiveObject::setGamePtr(&game);

    auto camera = std::make_shared<Camera>();
    Renderer::Get().SetCamera(camera);
    collisionManager.SetCamera(camera);

    // Initialize GLFW Callbacks and Inputs
    InputHandler inputHandler;
    CallbackPtr callbackPtr(camera);
    inputHandler.SetCallback(window, callbackPtr);
    
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    glEnable(GL_DEPTH_TEST);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Handle Inputs
        inputHandler.ProcessInput(window, camera, deltaTime, collisionManager);

        // View Matrix
        Renderer::Get().ComputeViewMatrix();

        // Render Clear       
        glClearColor(0.25f, 0.25f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check Collisions
        collisionManager.CheckCollisions();

        // Render scene
        scene.Draw();

        // Render Hud
        Hud::get().draw(camera, game, windowObject);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    Hud::get().free();
    scene.Free();
}