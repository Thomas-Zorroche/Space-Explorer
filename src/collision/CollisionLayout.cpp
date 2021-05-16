#include "CollisionLayout.hpp"

#include "game/InteractiveObject.hpp"


CollisionLayout::CollisionLayout(bool collision, bool stopMovement, InteractiveObject* object)
	: _hasCollision(collision), _canStopMovement(stopMovement), _objectPtr(object) {}

bool CollisionLayout::HasCollision() const 
{ 
	return _hasCollision; 
}

bool CollisionLayout::CanStopMovement() const 
{ 
	return _canStopMovement; 
}

void CollisionLayout::Function() const
{
	if (_objectPtr)
		_objectPtr->onOverlapEvent();
}