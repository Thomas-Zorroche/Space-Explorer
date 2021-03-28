#include "Game.hpp"

Game::Game(float size)
	: _WORLD_SIZE(size), _spaceship(nullptr)
{
	_spaceship = std::make_shared<Spaceship>(10, 0.2);
}

void Game::addHint(const std::string& hint)
{
	_hints.push_back(hint);
}

