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


Scene::Scene(float size, const std::shared_ptr<Galaxy>& galaxy)
	:  _skybox(nullptr), _galaxy(galaxy), _size(size)
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

	// Create Hints Objects
	// =================================================
	std::shared_ptr<InteractiveObject> hintTest1 = std::make_shared<Hint>(
		TransformLayout(),
		"Le niveau de radioactivite de doit \n pas etre au dessus de 0.3");
	/*std::shared_ptr<InteractiveObject> hintTest2 = std::make_shared<Hint>(
		TransformLayout(glm::vec3(190, 0, 201), glm::vec3(0), 0.2),
		"L eau, c est pour les faibles.");
	std::shared_ptr<InteractiveObject> hintTest3 = std::make_shared<Hint>(
		TransformLayout(glm::vec3(210, -1, 195), glm::vec3(0), 0.2),
		"Une atmosphere est necessaire.");*/
	_interactiveObjects = std::vector<std::shared_ptr<InteractiveObject> >({ hintTest1 } );
	probas::testBinomialProbability(1e6);
    probas::testBernoulliProbability(1e6);
    probas::testPoissonProbability(1e6);
    probas::testGeometricalProbability(1e6);

	// Load All Lights
	// =================================================
	LightManager::Get().LoadAllLights(_size);
}

void Scene::Draw(const std::shared_ptr<Camera>& camera)
{
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

