#pragma once

#include "probas.hpp"
#include <numeric>

namespace probas
{
    void testBinomialProbability(int nb_experiences);
    void testBernoulliProbability(int nb_experiences);
    void testPoissonProbability(int nb_experiences);
    void testGeometricalProbability(int nb_experiences);
};