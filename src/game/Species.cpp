#include "Species.hpp"
#include "Planet.hpp"

Species::Species(int techLevel): _techLevel(techLevel), _planetSettings(PlanetSettings::generatePlanetSettings())
{
    _name = Species::generateName(probas::discreteUniformDistribution(3, 6));
}

const PlanetSettings& Species::planetSettings() const
{ 
	return _planetSettings;
}

float Species::correlationCoefficient(const std::shared_ptr<Planet>& planet) const
{
	return _planetSettings.correlationCoefficient(planet->settings());
}

std::string Species::generateName(const int& nb_syllabes)
{
    std::vector<std::string> syllabes = { "bra", "cha", "zu", "bro", "tan", "noi", "pon", "chè", "gu", "tin", "soi", "grou" };
    std::string name;
    for(int i = 0; i < nb_syllabes; i++)
        name += syllabes.at(probas::discreteUniformDistribution(0, syllabes.size() - 1));
    name[0] = std::toupper(name[0]);
    return name;
}


