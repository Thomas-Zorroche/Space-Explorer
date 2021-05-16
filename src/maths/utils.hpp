#pragma once

#include "glm/glm.hpp"
#include <string>

double distanceSqr(const glm::vec3& A, const glm::vec3& B);
const glm::vec3 randomColor(float minThreshold = 0.0f);
std::string generateName(const int& nb_syllabes);