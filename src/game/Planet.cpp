#include "Planet.hpp"

Planet::Planet(glm::vec3 position, float radius)
	: CelestialBody(
	  StaticMesh(Model("res/models/sphere.obj"), TransformLayout(position), "DefaultLighting"), 
	  position
	  ),
	  _radius(radius)
{

}
