
#pragma once
#include "engine/Application.hpp"
#include "glm/glm.hpp"
#include "hud/PannelUI.hpp"
#include "hud/PanelSettings.hpp"
#include "game/PlanetSettings.hpp"
#include "game/CelestialBody.hpp"


#include <memory>

class Camera;
class Window;
class Game;
class Camera;
class Planet;

class Hud
{
public:
	static Hud& get()
	{
		static Hud instance;
		return instance;
	}

	Hud(const Hud&) = delete;
	Hud& operator=(const Hud&) = delete;

	void draw(const std::shared_ptr<Camera>& camera, Game& game, const Window& windowObject) const;
	void init(GLFWwindow* window, float width, float height);
	void free();

	void debugMode();
	void setCollisionInfo(int activeSpheresCount);

	void setFocusPosition(const std::shared_ptr<CelestialBody>& focusPlanet, const std::shared_ptr<Camera>& camera);
	void disableFocusPanel();

	void hideHintPanel();

	void displayLoadingWindow(float rate, GLFWwindow* window) const;

private:
	Hud() = default;
	~Hud() = default;

	void displayPlanetPanel(const Game& game) const;
	void displayEndgamePanel(const Game& game) const;
	void displayPlanetSettings(const PlanetSettings& settings, const Game& game, bool species = false) const;
	void displayLevelWindow(Game& game, const std::shared_ptr<Camera>& camera) const;

private:
	bool _debugMode = false;
	
	int _activesSpheresCount = 0;
	
	std::shared_ptr<CelestialBody> _focusPlanet = nullptr;

	PanelUI _focusPanel = PanelUI("res/img/Focus.png", "ui", 0, 0, 0.5);

	PanelSettings _panelSettings;

	bool _hideHintPanel = true;
};