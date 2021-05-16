#include "engine/Scene.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Renderer.hpp"
#include "engine/Skybox.hpp"
#include "engine/StaticMesh.hpp"
#include "engine/HintsImporter.hpp"

#include "opengl/Shader.h"

#include "lighting/LightManager.hpp"
#include "lighting/PointLight.hpp"
#include "lighting/DirectionalLight.hpp"

#include "game/Galaxy.hpp"
#include "game/Planet.hpp"
#include "game/CelestialBody.hpp"
#include "game/InteractiveObject.hpp"
#include "game/Hint.hpp"

#include "maths/testProbas.hpp"

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>


Scene::Scene(float size, const Game& game)
	:  _skybox(nullptr), _galaxy(game.galaxy()), _size(size)
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

	// Load All Lights
	// =================================================
	LightManager::Get().LoadAllLights(_size);
}

void Scene::Draw(const std::shared_ptr<Camera>& camera, const Game& game)
{
	if (_interactiveObjects.empty() && game.run())
		LoadHints(game);

	// Render the Skybox
	// =================================================
	_skybox->Draw();

	// Render the Skybox
	// =================================================
	if (_galaxy)
		_galaxy->draw(camera);

	// Render all the interactive objects
	// =================================================
	for (size_t i = 0; i < _interactiveObjects.size(); i++)
	{
		if (_interactiveObjects[i]->isActive()) 
			_interactiveObjects[i]->draw();
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

void Scene::LoadHints(const Game& game)
{
	std::cout << "LOAD HINTS" << std::endl;

	HintsImporter::setLevel(game.getDifficultyLevel());

	const auto& hints = HintsImporter::Hints("../res/game/hints.ini", game.getSpecies());

	for (const auto& hint : hints)
	{
		_interactiveObjects.push_back(hint);
	}
}

