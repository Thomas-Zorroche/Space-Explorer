#pragma once

#include <string>
#include "glm/glm.hpp"

class PlanetSettings
{
public:
	// Planet Constructor
	PlanetSettings(
		const std::string& name,
		float radius,
		int temperature,
		bool telluric,
		const glm::vec3& color,
		bool hasWater,
		bool atmosphere,
		bool magnetosphere,
		float radioactivityLevel,
		bool star = false)
		: _name(name), _radius(radius), _color(color), _temperature(temperature), 
		_telluric(telluric), _hasWater(hasWater), _atmosphere(atmosphere),
		_magnetosphere(magnetosphere), _radioactivityLevel(radioactivityLevel), _star(star) {}

	// Species Constructor
	PlanetSettings(
		int temperature,
		bool telluric,
		bool hasWater,
		bool atmosphere,
		bool magnetosphere,
		float radioactivityLevel)
		: _name(""), _radius(-1), _color(glm::vec3(0)), _temperature(temperature), 
		_telluric(telluric), _hasWater(hasWater), _atmosphere(atmosphere), 
		_magnetosphere(magnetosphere), _radioactivityLevel(radioactivityLevel), _star(false) {}


	// Getters
	// ===============================
	const std::string& name() const { return _name; }
	float radius() const { return _radius; }
	const glm::vec3& color() const { return _color; }
	int temperature() const { return _temperature; }
	bool telluric() const { return _telluric; }
	bool hasWater() const { return _hasWater; }
	bool atmosphere() const { return _atmosphere; }
	bool magnetosphere() const { return _magnetosphere; }
	float radioactivityLevel() const { return _radioactivityLevel; }
	bool star() const { return _star; }

	float correlationCoefficient(const PlanetSettings& planet) const
	{
		// Test if (this) is a species
		if (_radius != -1)
			return 0;

		float score = 1.0f;

		// Float values
		score += abs(_temperature - planet._temperature);
		score += abs(_radioactivityLevel - planet._radioactivityLevel);

		// Boolean values
		score += _telluric == planet._telluric ? 0 : 100.0f;
		score += _hasWater == planet._hasWater ? 0 : 100.0f;
		score += _atmosphere == planet._atmosphere ? 0 : 100.0f;
		score += _magnetosphere == planet._magnetosphere ? 0 : 100.0f;

		return score;
	}

private:
	std::string _name;	// Species Non-Essential
	float _radius;		// Species Non-Essential
	glm::vec3 _color;	// Species Non-Essential
	
	int _temperature;
	bool _telluric;
	bool _hasWater;
	bool _atmosphere;
	bool _magnetosphere;
	float _radioactivityLevel;

	bool _star;
};