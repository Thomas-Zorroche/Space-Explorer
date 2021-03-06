#pragma once

#define _USE_MATH_DEFINES
#define NOMINAX // Avoid conflicts between min and max constants in Windef.h

#include <iostream>
#include <algorithm>
#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "engine/Application.hpp"
#include "game/Spaceship.hpp"
#include "common.hpp"


class Terrain;

class Camera
{
public:
	Camera(float x, float z);
	~Camera() {}


	void Move(float deltaTime, DIRCAM dir);

	void rotateUp(float angle);
	void rotateLeft(float angle);

	// Getters Camera Data
	float GetFov() const { return _fov; }
	float GetWidth() const { return _widthScreen; }
	float GetHeight() const { return _heightScreen; }
	float GetNearPlane() const { return _nearPlane; }
	float GetFarPlane() const { return _farPlane; }
	inline glm::mat4 getViewMatrix() const 	{ return glm::lookAt(_Position, _Position + _FrontVector, _UpVector); }
	// Getters Camera Gameplay
	bool GetCanTurn() const  { return _CanTurn; }
	float GetLastX() const  { return _lastX; }
	float GetLastY() const  { return _lastY; }
	float GetSensitivity() const  { return _sensitivity; }
	glm::vec3 GetPosition() const { return _Position; };
	glm::vec3 GetFrontVector() const { return _FrontVector; };

	void RotateAroundPlanet(bool rotate, const glm::vec3& planetPosition = glm::vec3(0));
	
	// Setters
	void SetCanTurn(bool condition) { _CanTurn = condition; }
	void SetLastX(float x) { _lastX = x; }
	void SetLastY(float y) { _lastY = y; }

	bool isInOrbit() const { return _inOrbit; }
	void inOrbit(bool orbit) { _inOrbit = orbit; }

private:
	void computeDirectionVectors();
	void MoveX(float dst, const glm::vec3& dir);
	void MoveZ(float dst, const glm::vec3& dir);


	glm::vec3 _Position;			  // Position of the camera
	float _phi;
	float _theta;

	glm::vec3 _FrontVector;   // Direction
	glm::vec3 _LeftVector;    // Left
	glm::vec3 _UpVector;      // Up

	bool _CanTurn;    // Is Able to Turn ?
	float _lastX;     // Last Mouse coordinates
	float _lastY;

	// Input Data
	float _sensitivity;
	float _limitNormal = 2.0f;			// Limit value normal where the player can move
	float _responsiveness = 10.0f;       // Value use for lerp
	float _cameraTime = 0.0f;
	float _frequenceShake = 12.0f;
	float _amplitudeShake = 3.5f;
	bool _rotateAroundPlanet = false;
	glm::vec3 _rotationPoint;

	// Technical Data
	float _fov = 45.0f;
	float _widthScreen = 1280.0;
	float _heightScreen = 720.0;
	float _nearPlane = 0.1f;
	float _farPlane = 5000.0f;

	bool _inOrbit = false;

};