#include "CollisionManager.hpp"
#include "collision/CollisionGrid.hpp"
#include "collision/BoundingSphere.hpp"

#include "hud/Hud.hpp"

CollisionManager::CollisionManager(float worldSize)
	: _grid(worldSize), _WORLD_SIZE(worldSize)
{
	for (size_t i = (size_t)0; i < (size_t)_grid.Resolution(); i++)
	{
		for (size_t j = (size_t)0; j < (size_t)_grid.Resolution(); j++)
		{
			_spheres.insert({
				CollisionGridCase(i, j),
				std::vector<std::shared_ptr<BoundingSphere> >()
			});
		}
	}
}

void CollisionManager::CheckCollisions(Game& game)
{
	// Retrieve all active boxes from the current grid case where the player is moving
	glm::vec3 cameraPosition = _camera->GetPosition();
	CollisionGridCase playerCase = _grid.getCase(cameraPosition);
	auto& activeSpheres = _spheres[playerCase];

	// Check all collisions between spheres and camera
	int countCollision = 0;
	_camera->RotateAroundPlanet(false);
	bool inOrbit = false;
	for (size_t i = (size_t)0; i < activeSpheres.size(); i++)
	{
		bool hit = activeSpheres[i]->isPointInsideSphere(cameraPosition);
		if (_debugMode) activeSpheres[i]->draw();
		
		// If colliding, execute appropriate event
		if (hit)
		{
			if (activeSpheres[i]->StopPlayerMovement()) // WARNING : We suppose that it is a planet
			{
				glm::vec3 cameraToPlanet = activeSpheres[i]->center() - _camera->GetPosition();
				// We have to prevent movement if the player go in the direction of the planet
				// Two cases :
				// The player moves forward : if FrontVector . cameraToPlanet is POSITIVE, prevent move
				// The player moves backward : FrontVector . cameraToPlanet is NEGATIVE, prevent move
				if ((game.spaceship()->getDirection() == DIRCAM::FRONT && glm::dot(_camera->GetFrontVector(), cameraToPlanet) > 0) ||
					(game.spaceship()->getDirection() == DIRCAM::BACK && glm::dot(_camera->GetFrontVector(), cameraToPlanet) < 0))
				{
					game.spaceship()->decelerate(5);
				}

				_camera->RotateAroundPlanet(true, activeSpheres[i]->center());
				inOrbit = true;
			}

			activeSpheres[i]->onBeginOverlap();
			countCollision++;
		}
	}

	_camera->inOrbit(inOrbit);
	Hud::get().setCollisionInfo(activeSpheres.size());
}

void CollisionManager::AddSphere(const std::shared_ptr<BoundingSphere>& sphere)
{
	// Retrive case coordinates of the sphere
	CollisionGridCase sphereCase = _grid.getCase(sphere);

	// Add the sphere to the right case
	_spheres[sphereCase].push_back(sphere);
	sphere->AddIndex(sphereCase, _spheres[sphereCase].size() - 1);

	// Check whether the sphere is close to others cases 
	bool insideLeft = false, insideRight = false;
	if (sphereCase.Y > 0 && sphere->center().z <= (sphereCase.Y * _grid.WidthCase()) + sphere->radius())
	{
		// LEFT
		addSphereIntoCase(sphere, sphereCase.X, sphereCase.Y - 1);
		insideLeft = true;
	}
	else if (sphereCase.Y < _grid.Resolution() && sphere->center().z >= ((sphereCase.Y * _grid.WidthCase()) + _grid.WidthCase()) - sphere->radius())
	{
		// RIGHT
		addSphereIntoCase(sphere, sphereCase.X, sphereCase.Y + 1);
		insideRight = true;
	}
	if (sphereCase.X > 0 && sphere->center().x <= (sphereCase.X * _grid.WidthCase()) + sphere->radius())
	{
		// BOTTOM
		addSphereIntoCase(sphere, sphereCase.X - 1, sphereCase.Y);
		if (insideLeft) addSphereIntoCase(sphere, sphereCase.X - 1, sphereCase.Y - 1); // BOTTOM LEFT
		if (insideRight) addSphereIntoCase(sphere, sphereCase.X - 1, sphereCase.Y + 1); // BOTTOM RIGHT
	}
	else if (sphereCase.X < _grid.Resolution() && sphere->center().x >= ((sphereCase.X * _grid.WidthCase()) + _grid.WidthCase()) - sphere->radius())
	{
		// TOP
		addSphereIntoCase(sphere, sphereCase.X + 1, sphereCase.Y);
		if (insideLeft) addSphereIntoCase(sphere, sphereCase.X + 1, sphereCase.Y - 1); // TOP LEFT
		if (insideRight) addSphereIntoCase(sphere, sphereCase.X + 1, sphereCase.Y + 1); // TOP RIGHT
	}
}

void CollisionManager::addSphereIntoCase(const std::shared_ptr<BoundingSphere>& sphere, int X, int Y)
{
	CollisionGridCase sphereCase(X, Y);
	_spheres[sphereCase].push_back(sphere);
	sphere->AddIndex(sphereCase, _spheres[sphereCase].size() - 1);
}

void CollisionManager::DeleteSphere(const std::shared_ptr<BoundingSphere>& sphere)
{
	// Delete all references of the box in cases
	for (auto it = sphere->Indices().begin(); it != sphere->Indices().end(); ++it)
	{
		_spheres[it->first].erase(_spheres[it->first].begin() + it->second);
		updateCaseIndices(it->first, it->second);
	}
	sphere->Indices().clear();
}

void CollisionManager::updateCaseIndices(const CollisionGridCase& gridCase, int indexDeadSphere)
{
	for (size_t i = indexDeadSphere; i < _spheres[gridCase].size(); i++)
		_spheres[gridCase][i]->DecreaseIndexCase(gridCase);
}

void CollisionManager::debugMode()
{
	_debugMode = _debugMode ? false : true;
}
