#include "Game.hpp"
#include "PlanetSettings.hpp"
#include "Galaxy.hpp"
#include "Species.hpp"

Game::Game(float size)
	: _galaxy(std::make_shared<Galaxy>(size)),
	_species(std::make_shared<Species>(
		"Cho Chokolah", 
		15, 
		PlanetSettings(90, true, false, true, false, 0.15))),
	_spaceship(std::make_shared<Spaceship>(10, 0.2))
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
}


