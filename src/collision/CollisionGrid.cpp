#include "collision/CollisionGrid.hpp"
#include "collision/BoundingSphere.hpp"

CollisionGridCase CollisionGrid::getCase(const std::shared_ptr<BoundingSphere>& sphere)
{
	return CollisionGridCase(sphere->center().x / _widthCase, sphere->center().z / _widthCase);
}

CollisionGridCase CollisionGrid::getCase(const glm::vec3& point)
{
	return CollisionGridCase(point.x / _widthCase, point.z / _widthCase);
}