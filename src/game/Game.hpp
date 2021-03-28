#pragma once

#include <vector>
#include <string>

class Game
{
public:
	Game(float size = 1000.0f);

	void addHint(const std::string& hint);

	const std::vector<std::string>& hints() const { return _hints; } 

	float worldSize() const { return _WORLD_SIZE; }

private:
	std::vector<std::string> _hints;
	
	const float _WORLD_SIZE = 1000.f;
};