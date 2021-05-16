#pragma once

#include <vector>
#include <memory>
#include <string>

#include "engine/Application.hpp"
#include "game/Spaceship.hpp"
#include "common.hpp"

class Species;
class Galaxy;


class Game
{
public:
	Game(float size = 1000.0f, GLFWwindow * window = nullptr);

	void addHint(const std::string& hint);

	const std::vector<std::string>& hints() const { return _hints; } 

	const std::shared_ptr<Spaceship> spaceship() const { return _spaceship; }
	std::shared_ptr<Spaceship> spaceship() { return _spaceship; }

	void setEndgame() { _running = false; _endgame = true; }
	bool run() const { return _running; }
	bool endgame() const { return _endgame; }

	std::shared_ptr<Galaxy> galaxyPtr() { return _galaxy; }
	const std::shared_ptr<Galaxy> galaxy() const { return _galaxy; }
	const std::shared_ptr<Species> species() const { return _species; }

	void setDifficultyLevel(Difficulty::Level level);
	Difficulty::Level getDifficultyLevel() const { return _level; }

	std::shared_ptr<Species> getSpecies() const { return _species; }

private:
	void initialize();

private:
	std::vector<std::string> _hints;

	std::shared_ptr<Galaxy> _galaxy;
	std::shared_ptr<Species> _species = nullptr;
	std::shared_ptr<Spaceship> _spaceship = nullptr;;

	bool _running = false;
	bool _endgame = false;

	Difficulty::Level _level = Difficulty::Easy;
};