#pragma once

#include <vector>
#include <memory>
#include <string>
#include "game/Spaceship.hpp"

class Species;
class Galaxy;

class Game
{
public:
	Game(float size = 1000.0f);

	void addHint(const std::string& hint);

	const std::vector<std::string>& hints() const { return _hints; } 


	const std::shared_ptr<Spaceship> spaceship() const { return _spaceship; }
	std::shared_ptr<Spaceship> spaceship() { return _spaceship; }

	void setEndgame() { _endgame = true; }
	bool endgame() const { return _endgame; }

	std::shared_ptr<Galaxy> galaxyPtr() { return _galaxy; }
	const std::shared_ptr<Species> species() const { return _species; }

private:
	std::vector<std::string> _hints;

	std::shared_ptr<Galaxy> _galaxy;
	std::shared_ptr<Species> _species;
	std::shared_ptr<Spaceship> _spaceship;

	bool _endgame = false;

};