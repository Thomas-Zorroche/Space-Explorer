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
#include "hud/PannelUI.hpp"

void mainloop(Window& windowObject)
{
    GLFWwindow* window = windowObject.WindowPtr();
    
    // Load all the 
    ResourceManager::Get().LoadAllShaders();
    
    // Initialisation Collision Manager
    CollisionManager collisionManager(500.0f); // parameter: world size
    StaticMesh::SetCollisionManagerPtr(&collisionManager);

    Game game(collisionManager.worldSize());

    Scene scene(collisionManager.worldSize(), game.galaxyPtr());
    
    Hud::get().init(window, windowObject.Width(), windowObject.Height());

    InteractiveObject::setGamePtr(&game);

    auto camera = std::make_shared<Camera>(200, 230); // parameter: (x, z) spawn
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
        inputHandler.ProcessInput(window, camera, deltaTime, collisionManager, game);

        // View Matrix
        Renderer::Get().ComputeViewMatrix();

        // Render Clear       
        glClearColor(0.25f, 0.25f, 0.32f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check Collisions
        collisionManager.CheckCollisions(game);

        // Render scene
        scene.Draw(camera);

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