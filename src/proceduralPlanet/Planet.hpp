#pragma once

#include "TerrainFace.hpp"
#include "engine/StaticMesh.hpp"
#include "engine/Application.hpp"

#include "ShapeSettings.hpp"
#include "ColorSettings.hpp"
#include "ShapeGenerator.hpp"

#include "imgui/imgui_color_gradient.h"

#include <memory>
#include <string>
#include <list>

namespace proceduralPlanet
{

enum class ObserverFlag
{
	RESOLUTION = 0,
	COLOR,
	MESH
};

enum class FaceRenderMask
{
	All = 0,
	Top,
	Bottom,
	Left,
	Right,
	Front,
	Back
};

class Planet
{
public:
	Planet(int resolution = 64);

	void draw();

	std::shared_ptr<ShapeSettings> shapeSettings() { return _shapeSettings; }
	std::shared_ptr<ColorSettings> colorSettings() { return _colorSettings; }
	std::shared_ptr<ShapeGenerator> shapeGenerator() { return _shapeGenerator; }

	int& resolution() { return _resolution; }

	void update(ObserverFlag flag);

	void updateNoiseLayersCount(int noiseLayersCount);

	void reset();

	void Rotate(const glm::vec3& angles);

	FaceRenderMask& getFaceRenderMask() { return _faceRenderMask; }

	void RandomGenerate();

	std::shared_ptr<StaticMesh> GetStaticMesh() { return _staticMesh; }
	void sendUniforms(std::shared_ptr<Shader>& shader);

private:
	void generatePlanet();
	void generateMesh();
	void generateColors();

private:
	int _resolution;

	std::shared_ptr<ShapeSettings> _shapeSettings;
	std::shared_ptr<ColorSettings> _colorSettings;
	std::shared_ptr<ShapeGenerator> _shapeGenerator;

	TerrainFace _terrainFaces[6];
	std::shared_ptr<StaticMesh> _staticMesh;

	FaceRenderMask _faceRenderMask = FaceRenderMask::All;

	float _maxElevation = 0.0f;
};

} // ns Procedural Planet