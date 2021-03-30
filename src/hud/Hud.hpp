#pragma once
#include "engine/Application.hpp"
#include "glm/glm.hpp"
#include "hud/PannelUI.hpp"

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

	void draw(const std::shared_ptr<Camera>& camera, const Game& game,
		const Window& windowObject) const;
	void init(GLFWwindow* window);
	void free();

	void debugMode();
	void setCollisionInfo(int activeSpheresCount);

	void setFocusPosition(const std::shared_ptr<Planet>& focusPlanet, const std::shared_ptr<Camera>& camera);
	void disableFocusPanel();

private:
	Hud() = default;
	~Hud() = default;

	bool _debugMode = false;
	
	int _activesSpheresCount = 0;
	
	std::shared_ptr<Planet> _focusPlanet = nullptr;

	PanelUI _focusPanel = PanelUI("res/img/Focus.png", "ui", 0, 0, 0.5);
};