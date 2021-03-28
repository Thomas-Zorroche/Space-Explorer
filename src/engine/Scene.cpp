#include "engine/Scene.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Renderer.hpp"
#include "engine/Skybox.hpp"
#include "engine/StaticMesh.hpp"

#include "opengl/Shader.h"

#include "lighting/LightManager.hpp"
#include "lighting/PointLight.hpp"
#include "lighting/DirectionalLight.hpp"

#include "game/Galaxy.hpp"
#include "game/Planet.hpp"
#include "game/CelestialBody.hpp"
#include "game/InteractiveObject.hpp"
#include "game/Hint.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>


Scene::Scene(float size)
	:  _skybox(nullptr), _galaxy(nullptr), _size(size)
{
	Init();
}

Scene::~Scene() {}

void Scene::Init()
{
	// Create Skybox
	// =================================================
	std::vector<std::string> facesSkybox
	{
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"front.png",
		"back.png"
	};
	_skybox = std::make_shared<Skybox>(facesSkybox);

	// Create Galaxy
	// =================================================
	_galaxy = std::make_shared<Galaxy>(_size);

	// Create Interactive Objects
	// =================================================
	std::shared_ptr<InteractiveObject> hintTest1 = std::make_shared<Hint>(TransformLayout(glm::vec3(5, 0, 0), glm::vec3(0), 0.2), "X");
	std::shared_ptr<InteractiveObject> hintTest2 = std::make_shared<Hint>(TransformLayout(glm::vec3(0, 0, 5), glm::vec3(0), 0.2), "Z");
	std::shared_ptr<InteractiveObject> hintTest3 = std::make_shared<Hint>(TransformLayout(glm::vec3(0, 0, 0), glm::vec3(0), 0.2), "0");
	_interactiveObjects = std::vector<std::shared_ptr<InteractiveObject> >({ hintTest1, hintTest2, hintTest3 } );

	// Load All Lights
	// =================================================
	LightManager::Get().LoadAllLights();
}

void Scene::Draw()
{
	// Render the Skybox
	// =================================================
	_skybox->Draw();

	// Render the Skybox
	// =================================================
	_galaxy->draw();

	// Render all the interactive objects
	// =================================================
	for (size_t i = 0; i < _interactiveObjects.size(); i++)
	{
		if (_interactiveObjects[i]->isActive()) _interactiveObjects[i]->draw();
	}

	// Render all the static meshes
	// =================================================
	for (size_t i = 0; i < _staticMeshesCount; i++)
	{
		//_staticMeshes[i]->Draw();
	}
}

void Scene::AddStaticMesh(const std::shared_ptr<StaticMesh>& mesh)
{
	_staticMeshes.push_back(mesh);
	_staticMeshesCount++;
}

void Scene::Free()
{
	// Free all static meshes
	// =================================================
	for (size_t i = 0; i < _staticMeshesCount; i++)
		_staticMeshes[i]->Free();

	// Free all textures 
	// =================================================
	ResourceManager::Get().DeleteAllResources();
}

