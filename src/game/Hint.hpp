#pragma once

#include "game/InteractiveObject.hpp"
#include <string>
#include "glm/glm.hpp"

class TransfromLayout;

class Hint : public InteractiveObject
{
public:
	Hint(const TransformLayout& transform, const std::string& message, float velocity);

	void onOverlapEvent() override;

private:
	std::string _message;
};