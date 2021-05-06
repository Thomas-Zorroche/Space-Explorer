#pragma once
#include "glm/glm.hpp"

#include "common.hpp"

class Spaceship
{
public:
	Spaceship(float maxSpeed, float acceleration);
	
	float instantSpeed() const;

	void speedUp();
	void decelerate(float factor = 0.5f);

	void setDirection(DIRCAM dir) { _direction = dir; }
	DIRCAM getDirection() const { return _direction; }

	float getVelocityRate() const { return _velocity / _MAX_SPEED; }

private:
	const int _MAX_SPEED;
	const float _MIN_SPEED = 0.1;

	double _stepSpeed;
	double _acceleration;
	double _velocity;

	DIRCAM _direction = DIRCAM::FRONT;
	
};