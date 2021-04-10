#include "probas.hpp"

#include <cmath>


namespace probas
{
	// Loi uniforme continue [a ; b]
	int continuousUniformDistribution(int a, int b)
	{
		return rand() % ((b + 1) - a) + a;
	}

	// Loi uniforme discrete [a ; b]
	int discreteUniformDistribution(int a, int b)
	{
		return floor(continuousUniformDistribution(a, b));
	}

	// Coefficient binomial "r parmi n"
    int nCr(int n, int r)
    {
        if (r > n / 2) // Réduit nb intérations : nCr = nC(n-r)
            r = n - r;

        int value = 1;
        for (int i = 1; i <= r; i++) {
            value *= (n - r + i);
            value /= i;
        }

        return value;
    }

    double bernoulliProbability(float x, float p, float n = 1)
    {
	    return std::pow(p, x) * std::pow(1 - p, n - x);
    }

    double binomialProbability(int n, int k, float p)
    {
	    return nCr(n, k) * bernoulliProbability(static_cast<float>(k), p, static_cast<float>(n));
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

    void TestProbas() {
        std::cout << "20 parmi 30 = " << probas::nCr(30, 20) << std::endl;
	    std::cout << "Test loi binomiale : " << std::endl;
	    std::cout << "On lance une pièce de monnaie 8 fois, schéma de Bernoulli : n = 8, p = 0.5" << std::endl;
	    std::cout << "Succès = obtenir face. On note X le nombre de succès." << std::endl;
	    std::cout << "La probabilité théorique d'obtenir 4 fois face est :    P(X = 4) = " << probas::binomialProbability(
                8, 4, 0.5) << std::endl;

	    int lancer;
	    int sum_faces = 0;
	    std::vector<int> experiences;
        for (int i = 0; i < 1e6; ++i) {
            for (int j = 0; j < 8; ++j) {
                lancer = discreteUniformDistribution(0, 1);
                if (lancer == 0) // Si on fait "face"
                    sum_faces += 1;
            }
            experiences.push_back(sum_faces);
            sum_faces = 0;
        }

        float proba_Bernouilli = 0;
        for (auto e: experiences)
            if (e == 4)
                proba_Bernouilli += 1;
        std::cout << "En pratique, pour 1 000 000 d'expériences, on obtient : P(X = 4) = " << proba_Bernouilli / 1e6 << std::endl;
	}

}; // nos probas