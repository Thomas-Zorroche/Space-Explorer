#include "hud/Hud.hpp"

#include "engine/Camera.hpp"
#include "game/Game.hpp"
#include "game/Planet.hpp"
#include "engine/Window.hpp"
#include "engine/Renderer.hpp"
#include "engine/Camera.hpp"
#include "maths/utils.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


void Hud::init(GLFWwindow* window)
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
}

void Hud::draw(const std::shared_ptr<Camera>& camera, const Game& game,
    const Window& windowObject) const
{
    //New Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Main Board
    {
        ImGui::SetNextWindowPos(ImVec2(0, windowObject.Height() - 100));
        ImGui::SetNextWindowSize(ImVec2(windowObject.Width() - 500, 100));
        ImGui::Begin("Main Board");
        {
            ImGui::Text("Spaceship speed %f m/s", game.spaceship()->instantSpeed() * 100);
            if (_focusPanel.IsVisible())
            {
                ImGui::Text("Planet %s %g km", 
                    _focusPlanet->name().c_str(),
                    distanceSqr(camera->GetPosition(), _focusPlanet->position()));
            }
        }
        ImGui::End();
    }

    // Hints Pannel
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

    // Debug Pannel
    if (_debugMode)
    {
        ImGui::SetNextWindowPos(ImVec2(0.6 * windowObject.Width(), 0.05 * windowObject.Height()));
        ImGui::SetNextWindowSize(ImVec2(0.35 * windowObject.Width(), 0.1 * windowObject.Width()));
        ImGui::Begin("Debug Mode");
        {
            ImGui::Text("Position in the Galaxy (Camera)");
            ImGui::Text("X: %f ; Y: %f ; Z: %f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
            ImGui::Text("Actives spheres: %d", _activesSpheresCount);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
    }

    // Render ImGUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Render PanelUI
    if (_focusPanel.IsVisible()) _focusPanel.Draw();
}

void Hud::free()
{
    //Shutdown ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Hud::debugMode()
{
    _debugMode = _debugMode ? false : true;
}

void Hud::setCollisionInfo(int activeSpheresCount)
{
    _activesSpheresCount = activeSpheresCount;
}

void Hud::setFocusPosition(const std::shared_ptr<Planet>& focusPlanet, const std::shared_ptr<Camera>& camera)
{
    _focusPlanet = focusPlanet;
    glm::vec3 focusPosition = focusPlanet->position();
    glm::vec3 focusRadius = glm::vec3(focusPosition.x, focusPosition.y + focusPlanet->radius(), focusPosition.z);

    // Compute ndc coordinates of the center of the planet
    glm::vec4 clipSpacePos = Renderer::Get().Proj() * (Renderer::Get().View() * glm::vec4(focusPosition, 1.0));
    glm::vec3 ndcSpacePos = glm::vec3(clipSpacePos) / clipSpacePos.w;

    // Compute ndc coordinates of the radius of the planet
    glm::vec4 clipSpacePos_radius = Renderer::Get().Proj() * (Renderer::Get().View() * glm::vec4(focusRadius, 1.0));
    glm::vec3 ndcSpacePos_radius = glm::vec3(clipSpacePos_radius) / clipSpacePos_radius.w;

    _focusPanel.Place(ndcSpacePos.x, ndcSpacePos.y);

    double scaleFactor = 20 * distanceSqr(ndcSpacePos_radius, ndcSpacePos);

    std::cout << scaleFactor << std::endl;
    
    if (scaleFactor > 0.5) scaleFactor = 0.5;
    if (scaleFactor < 0.1) scaleFactor = 0.1;

    _focusPanel.Scale(scaleFactor);
    _focusPanel.setVisibility(true);
}

void Hud::disableFocusPanel()
{
    _focusPanel.setVisibility(false);
}




