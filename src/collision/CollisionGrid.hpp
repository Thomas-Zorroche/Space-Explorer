#pragma once

#include <memory>
#include "glm/glm.hpp"

class BoundingSphere;

struct CollisionGridCase
{
	int X, Y;

	CollisionGridCase(int x, int y)
		: X(x), Y(y) {}

	bool operator==(const CollisionGridCase& other) const
	{
		return (X == other.X && Y == other.Y);
	}
};

// custom specialization of std::hash
// Override operator() for using CollisionGridCase as a key in a unordered_map
namespace std
{
	template<>
	struct hash<CollisionGridCase>
	{
		std::size_t operator()(const CollisionGridCase& GridCase) const
		{
			// Compute individual hash values for X and Y
			std::size_t hX = std::hash<int>{}(GridCase.X);
			std::size_t hY = std::hash<int>{}(GridCase.Y);

			// and combine them using XOR and bit shifting
			return hX ^ (hY << hX);
		}
	};
}

class CollisionGrid
{
public:
	CollisionGrid(float size = 200.0f, int res = 10)
		: _size(size), _resolution(res) {}

	// Return the associate case where the sphere is currently on
	CollisionGridCase getCase(const std::shared_ptr<BoundingSphere>& sphere);

	// Return the associate case where the point is currently on
	CollisionGridCase getCase(const glm::vec3& point);

	int Resolution() const { return _resolution; }
	float Margin() const { return _margin; }
	float WidthCase() const { return _widthCase; }

private:

	// Equal to the size of the World
	float _size;
	int _resolution;
	float _widthCase = _size / (float)_resolution;
	float _margin = 0.2f; // We search around each case for potential object
						  // that are across multiple cases
};