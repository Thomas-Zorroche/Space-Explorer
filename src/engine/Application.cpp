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

    auto camera = std::make_shared<Camera>(200, 230); // parameter: (x, z) spawn
    Renderer::Get().SetCamera(camera);
    CollisionManager collisionManager(500.0f); // parameter: world size
    collisionManager.SetCamera(camera);
    
    // Load all the 
    ResourceManager::Get().LoadAllShaders();
    
    // Initialisation Collision Manager
    StaticMesh::SetCollisionManagerPtr(&collisionManager);

    Hud::get().init(window, windowObject.Width(), windowObject.Height());

    // Load all planets
    Game game(collisionManager.worldSize(), window);
    Scene scene(collisionManager.worldSize(), game);
    InteractiveObject::setGamePtr(&game);

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
        if (game.run())
            collisionManager.CheckCollisions(game);

        // Render scene
        scene.Draw(camera, game);

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