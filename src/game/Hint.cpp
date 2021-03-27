#include "game/Hint.hpp"
#include "engine/StaticMesh.hpp"
#include "game/Game.hpp"
#include <iostream>

Hint::Hint(const TransformLayout& transform, const std::string& message)
	: InteractiveObject(
		StaticMesh(Model("res/models/sphere.obj"), transform, "Default", CollisionLayout(true, false, this)),
		transform.Location()
	), 
	  _message(message)
{

}

void Hint::onOverlapEvent()
{
	std::cout << _message << std::endl;
	disable();
	InteractiveObject::_gamePtr->addHint(_message);
}
