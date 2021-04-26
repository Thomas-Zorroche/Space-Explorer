#include "proceduralPlanet/noise/NoiseSettings.hpp"

namespace proceduralPlanet
{

NoiseSettings::NoiseSettings()
{
};



FilterType& NoiseSettings::GetFilterType()
{
	return _filterType;
}

float NoiseSettings::strength() const { return _strength; }
float& NoiseSettings::strength() { return _strength; }

float NoiseSettings::baseRoughness() const { return _baseRoughness; }
float& NoiseSettings::baseRoughness() { return _baseRoughness; }

float NoiseSettings::roughness() const { return _roughness; }
float& NoiseSettings::roughness() { return _roughness; }

glm::vec3 NoiseSettings::center() const { return _center; }
glm::vec3& NoiseSettings::center() { return _center; }

int NoiseSettings::layersCount() const { return _layersCount; }
int& NoiseSettings::layersCount() { return _layersCount; }

float NoiseSettings::persistence() const { return _persistence; }
float& NoiseSettings::persistence() { return _persistence; }

float NoiseSettings::minValue() const { return _minValue; }
float& NoiseSettings::minValue() { return _minValue; }

float NoiseSettings::weightMultiplier() const { return _weightMultiplier; }
float& NoiseSettings::weightMultiplier() { return _weightMultiplier; }


}	// ns proceduralPlanet