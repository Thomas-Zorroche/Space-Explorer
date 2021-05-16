#include "engine/Camera.hpp"
#include "common.hpp"


Camera::Camera(float x, float z)
	: _Position(x, 0, z), _phi(M_PI), _theta(0), _CanTurn(true),
	_lastX(450.0f), _lastY(320.0f), _sensitivity(8.0f)
{
	computeDirectionVectors();
}

void Camera::Move(float deltaTime, DIRCAM direction)
{
	glm::vec3 dir;

	switch (direction)
	{
	case DIRCAM::FRONT:
		dir = _FrontVector;
		break;
	case DIRCAM::BACK:
		dir = -_FrontVector;
		break;
	case DIRCAM::LEFT:
		dir = _LeftVector;
		break;
	default:
		dir = _FrontVector;
		break;
	}

	float dst = deltaTime;

	MoveX(dst, dir);
	MoveZ(dst, dir);
	_Position.y += dst * dir.y;

	if (_rotateAroundPlanet)
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), _rotationPoint);
		modelMatrix = glm::rotate(modelMatrix, glm::radians(0.05f), glm::vec3(0.0, 1.0, 0.0));
		modelMatrix = glm::translate(modelMatrix, -_rotationPoint);

		_Position = modelMatrix * glm::vec4(_Position, 1.0);
	}

	computeDirectionVectors();
}


void Camera::rotateUp(float angle)
{
	_theta -= glm::radians(angle);
	computeDirectionVectors();
}
void Camera::rotateLeft(float angle)
{
	_phi -= glm::radians(angle);
	computeDirectionVectors();
}

void Camera::RotateAroundPlanet(bool rotate, const glm::vec3& planetPosition)
{
	if (rotate)
	{
		_rotateAroundPlanet = true;
		_rotationPoint = planetPosition;
	}
	else
	{
		_rotateAroundPlanet = false;
	}
}

/*
* Private Functions
*/
void Camera::computeDirectionVectors()
{
	// Direction
	_FrontVector = glm::vec3(glm::cos(glm::radians(_theta)) * glm::sin(glm::radians(_phi)),
		glm::sin(glm::radians(_theta)),
		glm::cos(glm::radians(_theta)) * glm::cos(glm::radians(_phi)));

	// Left
	_LeftVector = glm::vec3((glm::sin(glm::radians(_phi) + (M_PI / 2))),
		0,
		glm::cos(glm::radians(_phi) + (M_PI / 2)));

	// Up
	_UpVector = glm::cross(_FrontVector, _LeftVector);
}

void Camera::MoveX(float dst, const glm::vec3& dir)
{
	_Position.x += dst * dir.x;
}

void Camera::MoveZ(float dst, const glm::vec3& dir)
{
	_Position.z += dst * dir.z;
}


