#pragma once

#include <cstdlib>  // for rand(), srand()
#include <cmath>
#include <iostream>
#include <vector>

namespace probas
{
	// Loi uniforme continue [a ; b]
	int continuousUniformDistribution(int a, int b);
	// Loi uniforme discrete [a ; b]
	int discreteUniformDistribution(int a, int b);
	// Coefficient binomial
    int nCr(int n, int r);
    // Proba Binomiale
    float binomialProbabilty(int n, int k, float p);

    // Tests des probas
    void TestProbas();
}; // nos probas