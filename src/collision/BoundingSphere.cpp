#include "BoundingSphere.hpp"
#include "engine/Model.hpp"

#include <iostream>

BoundingSphere::BoundingSphere(const glm::vec3& center, int radius)
	: _center(center), _radius(radius)
		{}


void BoundingSphere::onBeginOverlap()
{
	std::cout << "COLLISION\n";
}

bool BoundingSphere::isPointInsideSphere(const glm::vec3& point) const
{
	float distance = ((point.x - _center.x) * (point.x - _center.x) +
				      (point.y - _center.y) * (point.x - _center.y) +
					  (point.z - _center.z) * (point.z - _center.z));

	float distanceSqr = distance * distance;

	return distanceSqr <= (_radius + (_radius * 0.2)) * (_radius + (_radius * 0.2));
}	

void BoundingSphere::scale(int alpha)
{ 
	_radius *= alpha; 
}

void BoundingSphere::translate(const glm::vec3& delta)
{
	_center = _center + delta;
}


void BoundingSphere::AddIndex(CollisionGridCase gridCase, int index)
{
	_indices.insert({ gridCase, index });
}

void BoundingSphere::DecreaseIndexCase(CollisionGridCase gridCase)
{
	_indices[gridCase] -= 1;
}



