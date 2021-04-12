#pragma once

#include <cstdlib>  // for rand(), srand()
#include <cmath>
#include <iostream>
#include <vector>

namespace probas
{
	// Loi uniforme continue [a ; b]
    float continuousUniformDistribution(float a, float b);
	// Loi uniforme discrete [a ; b]
	int discreteUniformDistribution(int a, int b);
	// Coefficient binomial
    int nCr(int n, int r);
    double binomialProbability(int n, int k, float p);
    double poissonProbability(int k, float lambda);
    double bernoulliProbability(int x, float p, int n = 1);
    double geometricalProbability(int k, float p);

}; // nos probas