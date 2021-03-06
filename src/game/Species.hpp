#pragma once

#include "PlanetSettings.hpp"
#include <string>
#include <memory>

class Planet;

class Species
{
public:
	Species(int techLevel);

	const PlanetSettings& planetSettings() const;

	float correlationCoefficient(const PlanetSettings& settings) const;

	std::string name() const { return _name; }

private:
	std::string _name;
	int _techLevel;
	PlanetSettings _planetSettings;
};