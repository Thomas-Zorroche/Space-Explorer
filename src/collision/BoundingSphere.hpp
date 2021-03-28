#pragma once

#include "glm/glm.hpp"
#include "collision/CollisionGrid.hpp"
#include "collision/CollisionLayout.hpp"
#include "engine/StaticMesh.hpp"

#include <memory>
#include <vector>
#include <unordered_map>

class BoundingSphere
{
public:
	BoundingSphere(const CollisionLayout& cLayout = CollisionLayout(), 
		const glm::vec3& center = glm::vec3(0, 0, 0), float radius = 1.0f);

	void onBeginOverlap();

	bool isPointInsideSphere(const glm::vec3& point) const;

	void scale(float alpha);
	void translate(const glm::vec3& delta);

	void update();

	const glm::vec3 center() const { return _center; }
	const float radius() const { return _radius; }

	bool StopPlayerMovement() const { return _cLayout.CanStopMovement(); }

	const std::unordered_map<CollisionGridCase, int>& Indices() const { return _indices; }
	std::unordered_map<CollisionGridCase, int>& Indices() { return _indices; }
	void AddIndex(CollisionGridCase gridCase, int index);
	void DecreaseIndexCase(CollisionGridCase gridCase);

	void draw();

private:
	glm::vec3 _center = glm::vec3(0, 0, 0);
	float _radius = 1.0f;

	Mesh _debugMesh;
	glm::mat4 _modelMatrix;

	std::unordered_map<CollisionGridCase, int> _indices;
	CollisionLayout _cLayout;
};