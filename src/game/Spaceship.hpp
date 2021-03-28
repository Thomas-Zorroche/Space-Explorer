#pragma once
#include "glm/glm.hpp"

class Spaceship
{
public:
	Spaceship(float maxSpeed, float acceleration);
	
	float instantSpeed() const;

	void update(const glm::vec3& lastFramePosition, const glm::vec3& cameraPosition, float deltaTime);

	void speedUp();
	void decelerate(float factor = 0.5f);

private:
	const int _MAX_SPEED;
	const float _MIN_SPEED = 0.1;

	double _stepSpeed;
	double _acceleration;
	double _velocity;
	
};