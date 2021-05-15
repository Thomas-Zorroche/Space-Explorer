#include "InteractiveObject.hpp"
#include "maths/probas.hpp"
#include <GLFW/glfw3.h>

Game* InteractiveObject::_gamePtr = nullptr;

void InteractiveObject::draw() 
{ 
	const glm::vec2 sunPosition = glm::vec2(250, 250);

	float i = _position.x - sunPosition.x;
	float j = _position.y - sunPosition.y;

	_mesh.ApplyTransforms();

	float x = i * cos(glm::radians((float)glfwGetTime() * _velocity)) - j * sin(glm::radians((float)glfwGetTime() * _velocity));
	float z = j * cos(glm::radians((float)glfwGetTime() * _velocity)) + i * sin(glm::radians((float)glfwGetTime() * _velocity));

	x += sunPosition.x;
	z += sunPosition.y;

	_mesh.Translate(glm::vec3(x, 0, z));

	_mesh.Rotate(glm::vec3((float)glfwGetTime() * _velocity));

	_mesh.Draw(); 
}


void InteractiveObject::disable()
{
	_active = false;
	_mesh.disableBoundingBox();
}
