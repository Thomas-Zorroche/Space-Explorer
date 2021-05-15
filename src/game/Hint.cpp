#include "game/Hint.hpp"
#include "engine/StaticMesh.hpp"
#include "game/Game.hpp"
#include <iostream>
#include <memory>

Hint::Hint(const std::string& message)
	: InteractiveObject(
		StaticMesh(std::make_shared<Model>("res/models/capsule.obj"), TransformLayout(), "Default", CollisionLayout(true, false, this))), 
	  _message(message)
{

}

void Hint::onOverlapEvent()
{
	std::cout << _message << std::endl;
	disable();

	InteractiveObject::_gamePtr->addHint(_message);
}
