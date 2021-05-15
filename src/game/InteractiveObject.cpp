#include "InteractiveObject.hpp"
#include <GLFW/glfw3.h>

Game* InteractiveObject::_gamePtr = nullptr;

void InteractiveObject::draw() 
{ 
	const glm::vec2 position = glm::vec2(300, 300);
	const glm::vec2 sunPosition = glm::vec2(250, 250);

	float i = position.x - sunPosition.x;
	float j = position.y - sunPosition.y;

	float velocity = 10;

	_mesh.ApplyTransforms();

	float x = i * cos(glm::radians((float)glfwGetTime() * velocity)) - j * sin(glm::radians((float)glfwGetTime() * velocity));
	float z = j * cos(glm::radians((float)glfwGetTime() * velocity)) + i * sin(glm::radians((float)glfwGetTime() * velocity));

	x += sunPosition.x;
	z += sunPosition.y;

	_mesh.Translate(glm::vec3(x, 0, z));

	_mesh.Rotate(glm::vec3((float)glfwGetTime() * velocity));

	_mesh.Draw(); 
}


void InteractiveObject::disable()
{
	_active = false;
	_mesh.disableBoundingBox();
}
