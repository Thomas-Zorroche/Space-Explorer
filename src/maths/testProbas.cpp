#include "testProbas.hpp"

namespace probas
{
    void testBinomialProbability(int nb_experiences)
    {
        std::cout << std::endl << "---------- DEBUT Test loi binomiale ----------" << std::endl;
        std::cout << "On lance une pièce de monnaie 8 fois, schéma de Bernoulli : n = 8, p = 0.5" << std::endl;
        std::cout << "Succès = obtenir face. On note X le nombre de succès." << std::endl;
        std::cout << "La probabilité théorique d'obtenir 4 fois face est :    P(X = 4) = " << probas::binomialProbability(
                8, 4, 0.5) << std::endl;

        int lancer;
        int sum_faces = 0;
        std::vector<int> experiences;
        for (int i = 0; i < nb_experiences; ++i) {
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
        std::cout << "En pratique, pour " << nb_experiences << " d'expériences, on obtient : P(X = 4) = " <<
                    proba_Bernouilli / static_cast<float>(nb_experiences) << std::endl;
        std::cout << "---------- FIN Test loi binomiale ----------" << std::endl;
    }

    void testBernoulliProbability(int nb_experiences)
    {
        std::cout << std::endl << "---------- DEBUT Test loi Bernoulli ----------" << std::endl;
        std::cout << "On détermine si une planète possède une atmoshpère." << std::endl;
        std::cout << "Succès = avoir une atmosphère. Proba du succès p = 0.13" << std::endl;
        std::cout << "La probabilité théorique d'obtenir une planètre avec atmosphère : P(X = 1) = " <<
                    probas::bernoulliProbability(1, 0.13) << std::endl;

        float lancer;
        int sum_ok = 0;
        for (int i = 0; i < nb_experiences; ++i) {
            lancer = continuousUniformDistribution(0, 1);
            if (lancer >= 0 && lancer <= 0.13)
                sum_ok += 1;
        }
        std::cout << "En pratique, pour " << nb_experiences << " d'expériences, on obtient : P(X = 1) = " <<
                    static_cast<float>(sum_ok) / static_cast<float>(nb_experiences) << std::endl;
        std::cout << "---------- FIN Test loi Bernoulli ----------" << std::endl;
    }
};
