#pragma once

class InteractiveObject;

// All data that define how the cBox will behave
class CollisionLayout
{
public:
	CollisionLayout(bool collision = true, bool stopMovement = true, InteractiveObject* object = nullptr);

	bool HasCollision() const;
	bool CanStopMovement() const;
	void Function() const;

	InteractiveObject* objectPtr() { return _objectPtr; }

private:
	// Whether cBox has Collision event or not
	bool _hasCollision;

	// Whether cBox can stop movement of the player or not
	bool _canStopMovement;

	// Pointer to the corresponding object
	InteractiveObject* _objectPtr;
};