#pragma once

#include <vector>
#include <memory>
#include <string>
#include "game/Spaceship.hpp"

class Game
{
public:
	Game(float size = 1000.0f);

	void addHint(const std::string& hint);

	const std::vector<std::string>& hints() const { return _hints; } 

	float worldSize() const { return _WORLD_SIZE; }

	const std::shared_ptr<Spaceship> spaceship() const { return _spaceship; }
	std::shared_ptr<Spaceship> spaceship() { return _spaceship; }

	void setEndgame() { _endgame = true; }
	bool endgame() const { return _endgame; }

private:
	std::vector<std::string> _hints;

	std::shared_ptr<Spaceship> _spaceship;

	bool _endgame = false;

	const float _WORLD_SIZE = 1000.f;
};