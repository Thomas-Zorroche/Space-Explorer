#include "Species.hpp"
#include "Planet.hpp"

Species::Species(int techLevel): _techLevel(techLevel), _planetSettings(PlanetSettings::generateSpeciesSettings())
{
    _name = generateName(probas::discreteUniformDistribution(3, 6));
}

const PlanetSettings& Species::planetSettings() const
{ 
	return _planetSettings;
}

float Species::correlationCoefficient(const PlanetSettings& settings) const
{
	return _planetSettings.correlationCoefficient(settings);
}


