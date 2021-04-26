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
    double bernoulliProbability(const int& x, const float& p, const int& n = 1);
    int simulateBernoulliProb(const float& p);
    double binomialProbability(const int& n, const int& k, const float& p);
    int simulateBinomialProb(const int& n, const float& p);
    double poissonProbability(const int& k, const float& lambda);
    int simulatePoissonProb(const float& lambda);
    double geometricalProbability(const int& k, const float& p);
    int simulateGeometricalProb(const float& p);

}; // nos probas