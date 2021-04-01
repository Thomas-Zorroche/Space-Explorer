#pragma once

#include <cstdlib>  // for rand(), srand()
#include <math.h>

namespace probas
{
	// Loi uniforme continue [a ; b]
	int continuousUniformDistribution(int a, int b);
	// Loi uniforme discr�te [a ; b]
	int discreteUniformDistribution(int a, int b);
}; // ns probas