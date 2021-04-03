#pragma once

#include "PlanetSettings.hpp"
#include <string>

class Species
{
public:
	Species(const std::string& name, int techLevel, const PlanetSettings& planetSettings);

	const PlanetSettings& bestPlanetSettings() const;

private:
	std::string _name;
	int _techLevel;
	PlanetSettings _bestPlanetSettings;
};