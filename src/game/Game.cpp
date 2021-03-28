#include "Game.hpp"

Game::Game(float size)
	: _WORLD_SIZE(size)
{

}

void Game::addHint(const std::string& hint)
{
	_hints.push_back(hint);
}

