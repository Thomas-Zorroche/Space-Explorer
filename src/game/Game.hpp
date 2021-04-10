#pragma once

#include <vector>
#include <memory>
#include <string>
#include "game/Spaceship.hpp"

class Species;
class Galaxy;

namespace Difficulty
{
	using Level = uint16_t;

	enum : Level
	{
		Easy = 0,
		Medium,
		Hard
	};

	static const char* LevelNames[] = { "Easy", "Medium", "Hard" };
}

class Game
{
public:
	Game(float size = 1000.0f);

	void addHint(const std::string& hint);

	const std::vector<std::string>& hints() const { return _hints; } 

	const std::shared_ptr<Spaceship> spaceship() const { return _spaceship; }
	std::shared_ptr<Spaceship> spaceship() { return _spaceship; }

	void setEndgame() { _running = false; _endgame = true; }
	bool run() const { return _running; }
	bool engame() const { return _endgame; }

	std::shared_ptr<Galaxy> galaxyPtr() { return _galaxy; }
	const std::shared_ptr<Galaxy> galaxy() const { return _galaxy; }
	const std::shared_ptr<Species> species() const { return _species; }

	void setDifficultyLevel(Difficulty::Level level);
	Difficulty::Level getDifficultyLevel() const { return _level; }

private:
	std::vector<std::string> _hints;

	std::shared_ptr<Galaxy> _galaxy;
	std::shared_ptr<Species> _species;
	std::shared_ptr<Spaceship> _spaceship;

	bool _running = false;
	bool _endgame = false;

	Difficulty::Level _level = Difficulty::Easy;
};