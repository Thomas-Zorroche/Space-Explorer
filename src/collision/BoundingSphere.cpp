#include "BoundingSphere.hpp"
#include "opengl/Sphere.hpp"
#include "engine/ResourceManager.hpp"
#include "opengl/Shader.h"
#include "engine/Renderer.hpp"

#include <iostream>

BoundingSphere::BoundingSphere(const glm::vec3& center, float radius)
	: _center(center), _radius(radius),
	_debugMesh(Mesh(Sphere().vertices(), ResourceManager::Get().CachePBRColorMaterial("cubeDebug", glm::vec3(1, 0, 0)))),
	_modelMatrix(glm::mat4(1.0f))
		{}


void BoundingSphere::onBeginOverlap()
{
	std::cout << "COLLISION\n";
}

bool BoundingSphere::isPointInsideSphere(const glm::vec3& point) const
{
	float distanceSqr = ((point.x - _center.x) * (point.x - _center.x) +
				      (point.y - _center.y) * (point.y - _center.y) +
					  (point.z - _center.z) * (point.z - _center.z));

	return distanceSqr <= _radius * _radius;
}	

void BoundingSphere::scale(float alpha)
{ 
	_radius *= alpha;
	update();
}

void BoundingSphere::translate(const glm::vec3& delta)
{
	_center += delta;
	update();
}

void BoundingSphere::update()
{
	_modelMatrix = glm::mat4(1.0f);
	_modelMatrix = _modelMatrix * glm::translate(glm::mat4(1.0f), _center);
	_modelMatrix = _modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(_radius));
}


void BoundingSphere::AddIndex(CollisionGridCase gridCase, int index)
{
	_indices.insert({ gridCase, index });
}

void BoundingSphere::DecreaseIndexCase(CollisionGridCase gridCase)
{
	_indices[gridCase] -= 1;
}

void BoundingSphere::draw()
{
	auto shader = ResourceManager::Get().GetShader("BoundingSphere");
	shader->Bind();

	Renderer::Get().SendTransMatrixUniforms(_modelMatrix, shader);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	_debugMesh.Draw(shader);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader->Unbind();
}




