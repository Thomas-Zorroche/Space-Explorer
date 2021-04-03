#include "Species.hpp"

Species::Species(
	const std::string& name, 
	int techLevel, 
	const PlanetSettings& planetSettings)
	: _name(name), _techLevel(techLevel), _bestPlanetSettings(planetSettings)
{

}

const Species::PlanetSettings& bestPlanetSettings() const 
{ 
	return _bestPlanetSettings; 
}

