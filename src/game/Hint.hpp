#pragma once

#include "game/InteractiveObject.hpp"
#include <string>
#include "glm/glm.hpp"

class TransfromLayout;

class Hint : public InteractiveObject
{
public:
	Hint(const std::string& message);

	void onOverlapEvent() override;

private:
	std::string _message;
};