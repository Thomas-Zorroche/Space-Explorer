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
		* Difficult = 70
		* Medium = 40
		* Easy = 10
		*/
		techLevel = 100 - ( ((int)_level + 1) * 30);
		_species = std::make_shared<Species>(15);
	}

	// Spaceship
	{
		_spaceship = std::make_shared<Spaceship>(10 * (techLevel / 100.0f), 0.2 + (techLevel / 100.0f));
	}
}


