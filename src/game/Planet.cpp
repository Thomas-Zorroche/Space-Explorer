#include "Planet.hpp"

Planet::Planet(glm::vec3 position, float radius)
	: CelestialBody(
	  StaticMesh(Model("res/models/planet01.obj"), TransformLayout(position, glm::vec3(0, 0, 0), radius), "Planet"), 
	  position
	  ),
	  _radius(radius)
{
}

