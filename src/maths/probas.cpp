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
    int nCr(const int& n, int r)
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

    double bernoulliProbability(const int& x, const float& p, const int& n)
    {
	    return std::pow(p, x) * std::pow(1 - p, n - x);
    }

    int simulateBernoulliProb(const float& p)
    {
	    return (continuousUniformDistribution(0, 1) <= p) ? 1 : 0;
    }

    double binomialProbability(const int& n, const int& k, const float& p)
    {
	    return nCr(n, k) * bernoulliProbability(k, p, n);
    }

    int simulateBinomialProb(const int& n, const float& p)
    {
	    int sum_success = 0;
        for(int i = 0; i < n; i++) {
            if(simulateBernoulliProb(p))
                sum_success++;
        }
        return sum_success;
    }

    double poissonProbability(const int& k, const float& lambda)
    {
	    auto value = pow(lambda, k) * std::exp(-lambda);
	    for (int i = 2; i <= k; i++)
	        value /= i;
	    return value;
    }

    int simulatePoissonProb(const float& lambda)
    {
        // D'après : http://math.univ-lille1.fr/~suquet/Polys/simul.pdf
        double x = continuousUniformDistribution(0, 1);
        int n = 0;
        while (x >= std::exp(-lambda)) {
            x *= continuousUniformDistribution(0, 1);
            n++;
        }
        return n;
    }

    double geometricalProbability(const int& k, const float& p)
    {
	    return std::pow(1 - p, k - 1) * p;
    }

    int simulateGeometricalProb(const float& p)
    {
        // D'après : http://math.univ-lille1.fr/~suquet/Polys/simul.pdf
        double x = continuousUniformDistribution(0, 1);
        int n = 1;
        while (x >= p) {
            x = continuousUniformDistribution(0, 1);
            n++;
        }
        return n;
    }

}; // nos probas