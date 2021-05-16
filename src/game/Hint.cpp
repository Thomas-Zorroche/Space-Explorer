#include "game/Hint.hpp"
#include "engine/StaticMesh.hpp"
#include "game/Game.hpp"
#include <iostream>
#include <memory>

Hint::Hint(const TransformLayout& transform, const std::string& message, float velocity)
	: InteractiveObject(
		StaticMesh(std::make_shared<Model>("res/models/capsule.obj"), transform, "Default", CollisionLayout(true, false, this)),
		transform.Location(),
		velocity
	), 
	  _message(message)
{

}

void Hint::onOverlapEvent()
{
	disable();
	InteractiveObject::_gamePtr->addHint(_message);
}
