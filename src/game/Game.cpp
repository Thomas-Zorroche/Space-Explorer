#include "Game.hpp"

Game::Game()
{

}

void Game::addHint(const std::string& hint)
{
	_hints.push_back(hint);
}

