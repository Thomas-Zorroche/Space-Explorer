#include "PlanetSettings.hpp"

float PlanetSettings::correlationCoefficient(const PlanetSettings& planet) const
{
    // Test if (this) is a species
    if (_radius != -1)
        return 0;

    float score = 1.0f;

    // Float values
    score += std::abs(_temperature - planet._temperature);
    score += std::abs(_radioactivityLevel - planet._radioactivityLevel);

    // Boolean values
    score += _telluric == planet._telluric ? 0 : 100.0f;
    score += _hasWater == planet._hasWater ? 0 : 100.0f;
    score += _atmosphere == planet._atmosphere ? 0 : 100.0f;
    score += _magnetosphere == planet._magnetosphere ? 0 : 100.0f;

    return score;
}

PlanetSettings PlanetSettings::generateSpeciesSettings()
{
    int temperature = probas::simulateBinomialProb(100, 0.3);
    bool telluric = probas::simulateBernoulliProb(0.4);
    bool hasWater = probas::simulateBernoulliProb(0.6);
    bool atmosphere = probas::simulateBernoulliProb(0.25);
    bool magnetosphere = probas::simulateBernoulliProb(0.12);
    float radioactivityLevel = probas::continuousUniformDistribution(0, 10);
    return PlanetSettings(temperature, telluric, hasWater, atmosphere, magnetosphere, radioactivityLevel);
}

PlanetSettings PlanetSettings::generatePlanetSettings(const float& dist_from_sun)
{
    std::string name = generateName(probas::discreteUniformDistribution(2, 5));
    float radius = probas::continuousUniformDistribution(0.5, 7);
    const glm::vec3& color = randomColor();
    int temperature = probas::simulateBinomialProb(100, 0.4);
    bool telluric = probas::simulateBernoulliProb(0.4);
    bool hasWater = probas::simulateBernoulliProb(0.6);
    bool atmosphere = probas::simulateBernoulliProb(0.25);
    bool magnetosphere = probas::simulateBernoulliProb(0.12);
    float radioactivityLevel = probas::continuousUniformDistribution(0, 10);
    return PlanetSettings(name, radius, temperature, telluric, color, hasWater, atmosphere, magnetosphere, radioactivityLevel);
}
