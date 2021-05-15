#include "Game.hpp"

#include "PlanetSettings.hpp"
#include "Galaxy.hpp"
#include "Species.hpp"

Game::Game(float size, GLFWwindow* window)
	: _galaxy(std::make_shared<Galaxy>(size, window))
{

}

void Game::addHint(const std::string& hint)
{
	_hints.push_back(hint);
}

void Game::setDifficultyLevel(Difficulty::Level level) 
{ 
	_level = level; 
	_running = true;

	// With the diffiuclty level, we can now create a specie, a spaceship and hints
	// ==========================================================================================
	initialize();
}

void Game::initialize()
{
	int techLevel = 0;
	// Species
	{
		const std::string speciesName = "Cho Chokolah";
		/*
		* Easy = 70
		* Medium = 40
		* Diffiuclt = 10
		*/
		techLevel = 100 - ( ((int)_level + 1) * 30);
		std::cout << techLevel << std::endl;
		_species = std::make_shared<Species>(15);
	}

	// Spaceship
	{
		float boost = 1;
		if (_level == Difficulty::Easy)		boost = 0.8;	// 2200
		if (_level == Difficulty::Medium)	boost = 1.2;	// 1900
		if (_level == Difficulty::Hard)		boost = 2.5;	// 1000

		_spaceship = std::make_shared<Spaceship>(40 * (techLevel / 100.0f) * boost, 0.2 + (techLevel / 100.0f));
	}
}


