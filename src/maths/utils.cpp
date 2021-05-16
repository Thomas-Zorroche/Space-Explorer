#include "utils.hpp"
#include "probas.hpp"

double distanceSqr(const glm::vec3& A, const glm::vec3& B)
{
	return ((B.x - A.x) * (B.x - A.x) +
		(B.y - A.y) * (B.y - A.y) +
		(B.z - A.z) * (B.z - A.z));
}

const glm::vec3 randomColor(float minThreshold)
{
	return glm::vec3(
		probas::discreteUniformDistribution(minThreshold, 1.0),
		probas::discreteUniformDistribution(minThreshold, 1.0),
		probas::discreteUniformDistribution(minThreshold, 1.0)
	);
}

std::string generateName(const int& nb_syllabes)
{
    std::vector<std::string> syllabes = { "bra", "cha", "zu", "bro", "tan", "noi", "pon", "chè", "gu", "tin", "soi", "grou" };
    std::string name;
    for(int i = 0; i < nb_syllabes; i++)
        name += syllabes.at(probas::discreteUniformDistribution(0, syllabes.size() - 1));
    name[0] = std::toupper(name[0]);
    return name;
}