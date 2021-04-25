#include "TerrainFace.hpp"
#include <vector>

namespace proceduralPlanet
{

glm::vec3 calculateSurfaceNormal(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C);

TerrainFace::TerrainFace(const std::shared_ptr<ShapeGenerator>& shapeGenerator, int resolution, const glm::vec3& localUp)
	: _mesh(std::make_shared<Mesh>()),
	_resolution(resolution),
	_localUp(localUp),
	_axisA(_localUp.y, _localUp.z, _localUp.x),
	_axisB(glm::cross(_localUp, _axisA)),
	_shapeGenerator(shapeGenerator)
{

}

/* Contruct a grid mesh for the face */
void TerrainFace::constructMesh()
{
	std::vector<ShapeVertex> vertices(_resolution * _resolution);
	std::vector<unsigned int> indices((_resolution - 1) * (_resolution - 1) * 6); 
	int triIndex = 0;
	_maxElevation = 0;


	// fill vertices and indices arrays
	for (size_t y = 0; y < _resolution; y++)
	{
		for (size_t x = 0; x < _resolution; x++)
		{
			int i = x + y * _resolution;
			glm::vec2 percent(x / (float)(_resolution - 1), y / (float)(_resolution - 1));
			glm::vec3 pointOnUnitCube = _localUp + ((percent.x - 0.5f) * 2 * _axisA) + ((percent.y - 0.5f) * 2 * _axisB);
			glm::vec3 pointOnUnitSphere = glm::normalize(pointOnUnitCube);
			
			float unscaledElevation = _shapeGenerator->calculateUnscaledElevation(pointOnUnitSphere);
			vertices[i].position = pointOnUnitSphere * _shapeGenerator->getScaledElevation(unscaledElevation);
			vertices[i].normal = glm::abs(_localUp);
			
			/*
			* U : ocean depths
			* V : 0
			*/
			vertices[i].texCoords = glm::vec2(unscaledElevation, 0);
			
			// Max elevation
			float elevation = glm::length(vertices[i].position);
			if (elevation > _maxElevation) _maxElevation = elevation;

			// Indices
			if (x != (_resolution - 1) && y != (_resolution - 1))
			{
				indices[triIndex++] = i;
				indices[triIndex++] = i + _resolution + 1;
				indices[triIndex++] = i + _resolution;

				indices[triIndex++] = i;
				indices[triIndex++] = i + 1;
				indices[triIndex++] = i + _resolution + 1;
			}
		}
	}

	_mesh->UpdateGeometry(vertices, indices);
}

void TerrainFace::updateResolution(int resolution)
{
	_resolution = resolution;
	constructMesh();
}

}	// ns proceduralPlanet

