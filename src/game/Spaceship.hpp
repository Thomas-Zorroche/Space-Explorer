#pragma once
#include "glm/glm.hpp"

class Spaceship
{
public:
	Spaceship(float maxSpeed, float acceleration);
	
	float instantSpeed() const;

	void update(const glm::vec3& lastFramePosition, const glm::vec3& cameraPosition, float deltaTime);

	void speedUp();
	void decelerate();

private:
	const int _MAX_SPEED;
	const int _MIN_SPEED = 0.3;

	double _stepSpeed;
	double _acceleration;
	double _velocity;
	
};