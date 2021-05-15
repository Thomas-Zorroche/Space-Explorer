#include "InteractiveObject.hpp"


Game* InteractiveObject::_gamePtr = nullptr;

void InteractiveObject::disable()
{
	_active = false;
	_mesh.disableBoundingBox();
}
