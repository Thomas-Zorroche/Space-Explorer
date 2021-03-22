#include "engine/Scene.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Renderer.hpp"
#include "engine/Skybox.hpp"

#include "opengl/Shader.h"

#include "lighting/LightManager.hpp"
#include "lighting/PointLight.hpp"
#include "lighting/DirectionalLight.hpp"

#include "game/Galaxy.hpp"
#include "game/Planet.hpp"
#include "game/CelestialBody.hpp"


#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>


Scene::Scene()
	:  _skybox(nullptr), _galaxy(nullptr)
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

	_galaxy = std::make_shared<Galaxy>();

	// Create all static meshes
	// =================================================
	Model m_sphere("res/models/sphere.obj");
	StaticMesh sun(m_sphere, TransformLayout(glm::vec3(0, 0, 0)), "DefaultLighting");
	sun.Scale(3);
	StaticMesh earth(m_sphere, TransformLayout(glm::vec3(10, 0, 10)), "DefaultLighting");

	AddStaticMesh(std::make_shared<StaticMesh>(sun));
	AddStaticMesh(std::make_shared<StaticMesh>(earth));

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

