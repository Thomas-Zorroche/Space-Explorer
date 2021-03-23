#pragma once

#include "glm/glm.hpp"
#include "collision/CollisionGrid.hpp"
#include <memory>
#include <vector>
#include <unordered_map>


class BoundingSphere
{
public:
	BoundingSphere(const glm::vec3& center = glm::vec3(0, 0, 0), int radius = 1);

	void onBeginOverlap();

	bool isPointInsideSphere(const glm::vec3& point) const;

	void scale(int alpha);
	void translate(const glm::vec3& delta);

	const glm::vec3 center() const { return _center; }

	bool StopPlayerMovement() const { return _stopPlayerMovement; }

	const std::unordered_map<CollisionGridCase, int>& Indices() const { return _indices; }
	std::unordered_map<CollisionGridCase, int>& Indices() { return _indices; }
	void AddIndex(CollisionGridCase gridCase, int index);
	void DecreaseIndexCase(CollisionGridCase gridCase);

private:
	glm::vec3 _center = glm::vec3(0, 0, 0);
	int _radius = 1;
	bool _stopPlayerMovement = true;

	std::unordered_map<CollisionGridCase, int> _indices;
};