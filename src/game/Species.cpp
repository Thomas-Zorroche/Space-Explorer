#include "Species.hpp"
#include "Planet.hpp"

Species::Species(
	const std::string& name, 
	int techLevel, 
	const PlanetSettings& planetSettings)
	: _name(name), _techLevel(techLevel), _planetSettings(planetSettings)
{

}

const PlanetSettings& Species::planetSettings() const
{ 
	return _planetSettings;
}

float Species::correlationCoefficient(const std::shared_ptr<Planet>& planet) const
{
	return _planetSettings.correlationCoefficient(planet->settings());
}


