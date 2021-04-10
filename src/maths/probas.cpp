#include "probas.hpp"

namespace probas
{
	// Loi uniforme continue [a ; b]
	float continuousUniformDistribution(float a, float b)
	{
		return a + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (b - a)));
	}

	// Loi uniforme discrete [a ; b]
	int discreteUniformDistribution(int a, int b)
	{
	    float value = continuousUniformDistribution(a, b);
		return (ceil(value) - value >= 0.5) ? ceil(value) : floor(value);
	}

	// Coefficient binomial "r parmi n"
    int nCr(int n, int r)
    {
        if (r > n / 2) // Réduit nb itérations : nCr = nC(n-r)
            r = n - r;

        int value = 1;
        for (int i = 1; i <= r; i++) {
            value *= (n - r + i);
            value /= i;
        }

        return value;
    }

    double bernoulliProbability(int x, float p, int n)
    {
	    return std::pow(p, x) * std::pow(1 - p, n - x);
    }

    double binomialProbability(int n, int k, float p)
    {
	    return nCr(n, k) * bernoulliProbability(k, p, n);
    }

    double poissonProbability(int k, int lambda)
    {
	    auto value = pow(lambda, k) * exp(-lambda);
	    for (int i = 2; i <= k; i++)
	        value /= i;
	    return value;
    }

    double geometricalProbability(int k, float p)
    {
	    return std::pow(1 - p, k - 1) * p;
    }

}; // nos probas