#pragma once

#include <vector>
#include <string>

class Game
{
public:
	Game();

	void addHint(const std::string& hint);

	const std::vector<std::string>& hints() const { return _hints; } 

private:
	std::vector<std::string> _hints;
};