#include "hud/Hud.hpp"

#include "engine/Camera.hpp"
#include "game/Game.hpp"
#include "game/Galaxy.hpp"
#include "game/Planet.hpp"
#include "game/Species.hpp"
#include "engine/Window.hpp"
#include "engine/Renderer.hpp"
#include "engine/Camera.hpp"
#include "maths/utils.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


void Hud::init(GLFWwindow* window, float width, float height)
{
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    // Init windows sizes
    _panelSettings.init(width, height);
}

void Hud::draw(const std::shared_ptr<Camera>& camera, Game& game,
    const Window& windowObject) const
{
    //New Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static bool demo = false;
    if (demo) ImGui::ShowDemoWindow(&demo);
    else
    {

    // Render PanelUI
    if (!camera->isInOrbit() && _focusPanel.IsVisible())
    {
        _focusPanel.Draw();
    }

    // Level Window
    if (!game.run() && !game.endgame())
        displayLevelWindow(game, camera);

    // Main Board
    if (game.run())
    {
        ImGui::SetNextWindowPos(ImVec2(_panelSettings.main[0], _panelSettings.main[1]));
        ImGui::SetNextWindowSize(ImVec2(_panelSettings.main[2], _panelSettings.main[3]));
        ImGui::Begin("Main Board");
        {
            ImGui::Text("Spaceship speed %f m/s", game.spaceship()->instantSpeed() * 100);

            ImGui::ProgressBar(game.spaceship()->getVelocityRate(), ImVec2(0.0f, 0.0f));

            if (!camera->isInOrbit() && _focusPanel.IsVisible())
            {
                ImGui::Text("Planet %s %g km",
                    _focusPlanet->name().c_str(),
                    distanceSqr(camera->GetPosition(), _focusPlanet->position()));
            }
            if (camera->isInOrbit())
            {
                ImGui::Text("Press A to land on %s", _focusPlanet->name().c_str());
            }
        }
        ImGui::End();
    }

    // Hints Pannel
    if (!_hideHintPanel && game.run())
    {
        ImGui::SetNextWindowPos(ImVec2(_panelSettings.hint[0] - 150, _panelSettings.hint[1]));
        ImGui::SetNextWindowSize(ImVec2(_panelSettings.hint[2] + 150, 200));
        ImGui::Begin("Hint Pannel");
        {
            for (const auto& hint : game.hints())
            {
                ImGui::Text(hint.c_str());
                ImGui::Separator();
            }
        }
        ImGui::End();
    }

    // Endgame Panel
    if (game.endgame())
        displayEndgamePanel(game);

    // Planet Window 
    if (game.run() && camera->isInOrbit())
    {
        displayPlanetPanel(game);
    }

    // Debug Pannel
    if (_debugMode)
    {
        ImGui::SetNextWindowPos(ImVec2(_panelSettings.debug[0], _panelSettings.debug[1]));
        ImGui::SetNextWindowSize(ImVec2(_panelSettings.debug[2], _panelSettings.debug[3]));
        ImGui::Begin("Debug Mode");
        {
            ImGui::Text("Position in the Galaxy (Camera)");
            ImGui::Text("Difficulty Level: %s", Difficulty::LevelNames[game.getDifficultyLevel()]);
            ImGui::Text("X: %f ; Y: %f ; Z: %f", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
            ImGui::Text("Actives spheres: %d", _activesSpheresCount);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();
    }
    
    }

    // Render ImGUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Hud::displayPlanetPanel(const Game& game) const
{
    ImGui::SetNextWindowPos(ImVec2(_panelSettings.planet[0], _panelSettings.planet[1]));
    ImGui::SetNextWindowSize(ImVec2(_panelSettings.planet[2], _panelSettings.planet[3]));
    ImGui::Begin("Planet Panel");
    {
        displayPlanetSettings(_focusPlanet->settings(), game);
    }
    ImGui::End();
}

void Hud::displayEndgamePanel(const Game& game) const
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    static bool endgameOpen = true;

    ImGui::SetNextWindowPos(ImVec2(_panelSettings.endgame[0], _panelSettings.endgame[1]));
    ImGui::SetNextWindowSize(ImVec2(_panelSettings.endgame[2], _panelSettings.endgame[3]));

    ImGui::Begin("Endgame", &endgameOpen, window_flags);
    {
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("Endgame", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("Galaxy Settings"))
            {
                ImGui::Text("You landed on %s, with a correlation coefficient of %f \n (1.0 is the best score)",
                    _focusPlanet->name().c_str(),
                    game.species()->correlationCoefficient(_focusPlanet->settings()));
                ImGui::NewLine();
                ImGui::Separator();

                if (ImGui::CollapsingHeader("Species"))
                {
                    ImGui::Text("Best Planet for %s Species", game.species()->name().c_str());
                    displayPlanetSettings(game.species()->planetSettings(), game, true);
                    ImGui::NewLine();
                    ImGui::Separator();
                }

                if (ImGui::CollapsingHeader("Planets"))
                {
                    // Display Planet Focus Settings
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(46, 196, 242)));
                    displayPlanetSettings(_focusPlanet->settings(), game);
                    ImGui::NewLine();
                    ImGui::Separator();
                    ImGui::PopStyleColor(1);
                    
                    // Display other planets
                    for (const auto& body : game.galaxy()->celestialBodies())
                    {
                        if (auto planet = std::dynamic_pointer_cast<Planet>(body))
                        {
                            if (planet->name() != _focusPlanet->name())
                            {
                                displayPlanetSettings(planet->settings(), game);
                                ImGui::NewLine();
                                ImGui::Separator();
                            }
                        }
                    }
                }

                ImGui::EndTabItem();
            }

            //if (ImGui::BeginTabItem("Statistiques"))
            //{

            //    ImGui::EndTabItem();
            //}
            
            ImGui::EndTabBar();
        }

    }
    ImGui::End();
}

void Hud::displayPlanetSettings(const PlanetSettings& settings, const Game& game, bool species) const
{
    if (!species)
    {
        ImGui::Text("Name: %s", settings.name().c_str());
        if (game.endgame())
            ImGui::Text("Correlation Score: %f", game.species()->correlationCoefficient(settings));
    }
    ImGui::Text("Avg Temperature: %d degrees C", settings.temperature());
    ImGui::Text("Radioaactivty Level: %f", settings.radioactivityLevel());

    if (settings.telluric()) ImGui::Text("Telluric");
    else ImGui::Text("Gaseous");

    if (settings.hasWater()) ImGui::Text("Has Water");
    else ImGui::Text("No Water");

    if (settings.atmosphere()) ImGui::Text("Has Atmosphere");
    else ImGui::Text("No Atmosphere");

    if (settings.magnetosphere()) ImGui::Text("Has Magnetosphere");
    else ImGui::Text("No Magnetosphere");
}

void Hud::displayLevelWindow(Game& game, const std::shared_ptr<Camera>& camera) const
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
    static bool levelOpen = true;

    ImGui::SetNextWindowPos(ImVec2(_panelSettings.endgame[0], _panelSettings.endgame[1]));
    ImGui::SetNextWindowSize(ImVec2(_panelSettings.endgame[2], 200));
    ImGui::Begin("Level of Difficulty", &levelOpen, window_flags);
    {
        ImGui::Text("You embody an individual of an alien species at the controls of a spaceship.This one is adrift and damaged,\n\
it must land on a planet as quickly as possible to carry out repairs.You are in a solar system made up of several planets.\n\
However, the on - board computer had been damaged so the ship is unable to tell you which planet to land on.\n\
Your objective is to explore the system for information on the various planetsand the species you play as.\n\
Your goal is therefore to find the planet in the system that best matches your species.");

        ImGui::Separator();

        ImGui::Text("Please, choose your level of difficulty");

        const Difficulty::Level all_Levels[] = {
            Difficulty::Easy, Difficulty::Medium, Difficulty::Hard,
        };

        for (const auto& lvl : all_Levels)
        {
            if (ImGui::Button(Difficulty::LevelNames[lvl]))
            {
                game.setDifficultyLevel(lvl);
                camera->SetCanTurn(true);
            }
            ImGui::SameLine();
        }
    }
    ImGui::End();
}

void Hud::displayLoadingWindow(float rate, GLFWwindow* window) const
{
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
    //New Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
    static bool loadingOpen = true;

    ImGui::SetNextWindowPos(ImVec2(_panelSettings.endgame[0], _panelSettings.endgame[1] + 200));
    ImGui::SetNextWindowSize(ImVec2(_panelSettings.endgame[2], 75));
    ImGui::Begin("Loading screen", &loadingOpen, window_flags);
    {
        ImGui::Text("Loading...");
        ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.99);
        ImGui::ProgressBar(rate, ImVec2(0.0f, 0.0f));
        ImGui::PopItemWidth();
        ImGui::Separator();
    }
    ImGui::End();

    // Render ImGUI
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
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

void Hud::setFocusPosition(const std::shared_ptr<CelestialBody>& focusPlanet, const std::shared_ptr<Camera>& camera)
{
    if (!camera->isInOrbit())
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

        double scaleFactor = 15 * distanceSqr(ndcSpacePos_radius, ndcSpacePos);

        if (scaleFactor > 0.5) scaleFactor = 0.5;
        if (scaleFactor < 0.1) scaleFactor = 0.1;

        _focusPanel.Place(ndcSpacePos.x, ndcSpacePos.y);
        //_focusPanel.Rotate(0.1 * glfwGetTime());
        _focusPanel.Scale(scaleFactor);
        _focusPanel.setVisibility(true);
    }
}

void Hud::disableFocusPanel()
{
    _focusPanel.setVisibility(false);
}

void  Hud::hideHintPanel()
{
    _hideHintPanel = _hideHintPanel ? false : true;
}





