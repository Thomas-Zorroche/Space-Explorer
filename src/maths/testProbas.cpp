#include "testProbas.hpp"

namespace probas
{
    void testBernoulliProbability(int nb_experiences)
    {
        float p = 0.13;
        int k = 1;
        std::cout << std::endl << "---------- DEBUT Test loi Bernoulli ----------" << std::endl;
        std::cout << "On détermine si une planète possède une atmoshpère." << std::endl;
        std::cout << "Succès = avoir une atmosphère. Proba du succès p = 0.13" << std::endl;
        std::cout << "La probabilité théorique d'obtenir une planète avec atmosphère : P(X = " << k << ") = " <<
                  probas::bernoulliProbability(k, p) << std::endl;

        int sum_success = 0;
        for(int i = 0; i < nb_experiences; i++)
            if(simulateBernoulliProb(p) == k)
                sum_success++;

        std::cout << "En pratique, pour " << nb_experiences << " d'expériences, on obtient : P(X = " << k << ") = " <<
                  static_cast<float>(sum_success) / static_cast<float>(nb_experiences) << std::endl;
        std::cout << "---------- FIN Test loi Bernoulli ----------" << std::endl;
    }

    void testBinomialProbability(int nb_experiences)
    {
        int n = 8;
        float p = 0.5;
        int k = 4;
        std::cout << std::endl << "---------- DEBUT Test loi binomiale ----------" << std::endl;
        std::cout << "On lance une pièce de monnaie " << n << " fois, schéma de Bernoulli : n = " << n << ", p = "<< p << std::endl;
        std::cout << "Succès = obtenir face. On note X le nombre de succès." << std::endl;
        std::cout << "La probabilité théorique d'obtenir 4 fois face est :    P(X = " << k << ") = " <<
                    probas::binomialProbability(n, k, p) << std::endl;

        int sum_success = 0;
        for (int i = 0; i < nb_experiences; ++i)
            if(probas::simulateBinomialProb(n, p) == k)
                sum_success++;

        std::cout << "En pratique, pour " << nb_experiences << " d'expériences, on obtient : P(X = " << k << ") = " <<
                    static_cast<float>(sum_success) / static_cast<float>(nb_experiences) << std::endl;
        std::cout << "---------- FIN Test loi binomiale ----------" << std::endl;
    }

    void testPoissonProbability(int nb_experiences)
    {
        float lambda = 10;
        int k = 6;
        std::cout << std::endl << "---------- DEBUT Test loi de Poisson ----------" << std::endl;
        std::cout << "On détermine la distance d'une planète par rapport à l'étoile du système." << std::endl;
        std::cout << "Paramètre lambda = " << lambda << " (en million de kilomètres)" << std::endl;
        std::cout << "La probabilité théorique d'obtenir une planète située à " << k << ".10⁶ km : P(X = "<< k <<") = "<<
                    probas::poissonProbability(k, lambda) << std::endl;

        int sum_success = 0;
        for (int i = 0; i < nb_experiences; i++)
            if(probas::simulatePoissonProb(lambda) == k)
                sum_success++;

        std::cout << "En pratique, pour " << nb_experiences << " d'expériences, on obtient : P(X = " << k << ") = " <<
                    static_cast<float>(sum_success) / static_cast<float>(nb_experiences) << std::endl;
        std::cout << "---------- FIN Test loi de Poisson ----------" << std::endl;
    }

    void testGeometricalProbability(int nb_experiences)
    {
        float p = 0.2;
        int k = 8;
        std::cout << std::endl << "---------- DEBUT Test loi Géométrique ----------" << std::endl;
        std::cout << "On détermine la syllabe à choisir parmi un ensemble de 10 syllabes." << std::endl;
        std::cout << "Paramètre p = " << p << std::endl;
        std::cout << "La probabilité théorique d'obtenir la syllabe n°8 de la liste : P(X = "<< k <<") = "
        <<probas::geometricalProbability(k, p) << std::endl;

        int sum_success = 0;
        for (int i = 0; i < nb_experiences; i++)
            if(probas::simulateGeometricalProb(p) == k)
                sum_success++;

        std::cout << "En pratique, pour " << nb_experiences << " d'expériences, on obtient : P(X = " << k << ") = " <<
                    static_cast<float>(sum_success) / static_cast<float>(nb_experiences) << std::endl;
        std::cout << "---------- FIN Test loi Géométrique ----------" << std::endl;
    }
};
