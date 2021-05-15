#include "InteractiveObject.hpp"

#include <GLFW/glfw3.h>

Game* InteractiveObject::_gamePtr = nullptr;

InteractiveObject::InteractiveObject(const StaticMesh& mesh)
	: _mesh(mesh) 
{
	// Random Distance from Sun

	// Random Position on Orbit
	
	_position = glm::vec3(200, 0, 200);
};

void InteractiveObject::draw() 
{ 
	/* ============== TEST =============== */
	const glm::vec3 sunPosition = glm::vec3(250, 0, 250);

	_mesh.Translate(sunPosition);
	_mesh.Rotate(glm::vec3(0, (float)glfwGetTime() * _VELOCITY, 0));
	_mesh.Translate(-sunPosition);

	_mesh.Translate(_position);
	_mesh.Rotate(glm::vec3((float)glfwGetTime() * _VELOCITY, (float)glfwGetTime() * _VELOCITY * 0.5, (float)glfwGetTime() * _VELOCITY * 1.5));
	_mesh.Scale(1);

	// Draw
	_mesh.Draw(); 
	_mesh.ApplyTransforms();
}


void InteractiveObject::disable()
{
	_active = false;
	_mesh.disableBoundingBox();
}
