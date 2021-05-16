#include "Spaceship.hpp"

Spaceship::Spaceship(float maxSpeed, float acceleration)
	: _MAX_SPEED(maxSpeed), _stepSpeed(_MIN_SPEED), _acceleration(acceleration), _velocity(_MIN_SPEED)
{

}

float Spaceship::instantSpeed() const
{
	return _velocity;
}

void Spaceship::speedUp()
{
	if (_velocity < _MAX_SPEED)
	{
		_stepSpeed += _acceleration;
		_velocity = exp(0.05 * _stepSpeed);
	}
	else
	{
		_velocity = _MAX_SPEED;
	}
}

void Spaceship::decelerate(float factor)
{
	if (_velocity > _MIN_SPEED)
	{
		_stepSpeed -= _acceleration * factor;
		_velocity = exp(0.05 * _stepSpeed);
	}
	else
	{
		_velocity = _MIN_SPEED;
	}
}
