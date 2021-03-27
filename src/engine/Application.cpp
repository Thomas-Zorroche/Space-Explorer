#include "engine/Application.hpp"
#include "engine/Renderer.hpp"
#include "engine/Camera.hpp"
#include "engine/Scene.hpp"
#include "engine/InputHandler.hpp"
#include "engine/ResourceManager.hpp"

#include "collision/CollisionManager.hpp"

#include "game/Game.hpp"
#include "game/InteractiveObject.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

    InteractiveObject::setGamePtr(&game);

    auto camera = std::make_shared<Camera>();
    Renderer::Get().SetCamera(camera);
    collisionManager.SetCamera(camera);

    // Initialize GLFW Callbacks and Inputs
    InputHandler inputHandler;
    CallbackPtr callbackPtr(camera);
    inputHandler.SetCallback(window, callbackPtr);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

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

        // ImGui
        //New Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Check Collisions
        collisionManager.CheckCollisions();

        // Render scene here
        scene.Draw();

        // ImGui Content
        {
            ImGui::SetNextWindowPos(ImVec2(0, windowObject.Height() - 100));
            ImGui::SetNextWindowSize(ImVec2(windowObject.Width() - 500, 100));
            ImGui::Begin("Main Board");
            {
            ImGui::Text("Position in the Galaxy");
            ImGui::Text("X: %f ; Y: %f ; Z: %f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }
            ImGui::End();
        }
        {
            ImGui::SetNextWindowPos(ImVec2(windowObject.Width() - 500, windowObject.Height() - 100));
            ImGui::SetNextWindowSize(ImVec2(500, 100));
            ImGui::Begin("Hint Pannel");
            {
                for (const auto& hint : game.hints())
                    ImGui::Text(hint.c_str());
            }
            ImGui::End();
        }

        // Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //Shutdown ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    scene.Free();
}