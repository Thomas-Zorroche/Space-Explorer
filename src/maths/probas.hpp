#pragma once

#include <cstdlib>  // for rand(), srand()

namespace probas
{
	// Loi uniforme continue [a ; b]
	int continuousUniformDistribution(int a, int b)
	{
		return rand() % ((b + 1) - a) + a;
	}

	// Loi uniforme discrète [a ; b]
	int discreteUniformDistribution(int a, int b) 
	{
		return floor(continuousUniformDistribution(a, b));
	}

}; // ns probas