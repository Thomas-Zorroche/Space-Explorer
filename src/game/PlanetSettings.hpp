#pragma once

#include <string>
#include "glm/glm.hpp"


class PlanetSettings
{
public:
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
		: _name(name), _radius(radius), _temperature(temperature), _telluric(telluric),
		_color(color), _hasWater(hasWater), _atmosphere(atmosphere), _magnetosphere(magnetosphere),
		_radioactivityLevel(radioactivityLevel), _star(star) {}

	// Getters
	// ===============================
	const std::string& name() const { return _name; }
	float radius() const { return _radius; }
	int temperature() const { return _temperature; }
	bool telluric() const { return _telluric; }
	const glm::vec3& color() const { return _color; }
	bool hasWater() const { return _hasWater; }
	bool atmosphere() const { return _atmosphere; }
	bool magnetosphere() const { return _magnetosphere; }
	float radioactivityLevel() const { return _radioactivityLevel; }
	bool star() const { return _star; }

private:
	std::string _name;
	float _radius;
	int _temperature;
	bool _telluric;
	glm::vec3 _color;
	bool _hasWater;
	bool _atmosphere;
	bool _magnetosphere;
	float _radioactivityLevel;

	bool _star;
};