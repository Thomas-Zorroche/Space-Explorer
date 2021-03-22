#include "Planet.hpp"

Planet::Planet(glm::vec3 position, float radius)
	: CelestialBody(
	  StaticMesh(Model("res/models/sphere.obj"), TransformLayout(position, glm::vec3(0, 0, 0), radius), "DefaultLighting"), 
	  position
	  ),
	  _radius(radius)
{

}
