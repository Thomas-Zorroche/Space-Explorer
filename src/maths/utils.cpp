#include "utils.hpp"
#include "probas.hpp"

double distanceSqr(const glm::vec3& A, const glm::vec3& B)
{
	return ((B.x - A.x) * (B.x - A.x) +
		(B.y - A.y) * (B.y - A.y) +
		(B.z - A.z) * (B.z - A.z));
}

const glm::vec3& randomColor(float minThreshold)
{
	return glm::vec3(
		probas::discreteUniformDistribution(minThreshold, 1.0),
		probas::discreteUniformDistribution(minThreshold, 1.0),
		probas::discreteUniformDistribution(minThreshold, 1.0)
	);
}