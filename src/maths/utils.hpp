#pragma once

#include "glm/glm.hpp"

double distanceSqr(const glm::vec3& A, const glm::vec3& B)
{
	return ((B.x - A.x) * (B.x - A.x) +
			(B.y - A.y) * (B.y - A.y) +
			(B.z - A.z) * (B.z - A.z));
}