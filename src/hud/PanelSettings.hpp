#pragma once

struct PanelSettings
{
	PanelSettings() {}

	void init(float w, float h)
	{
		main[0] = 0;
		main[1] = 0.85 * h;
		main[2] = 0.3 * w;
		main[3] = 0.15 * h;

		hint[0] = 0.7 * w;
		hint[1] = 0;
		hint[2] = 0.3 * w;
		hint[3] = h;

		planet[0] = 0.05 * w;
		planet[1] = 0.05 * w;
		planet[2] = 0.2 * w;
		planet[3] = 0.12 * w;

		debug[0] = 0.6 * w;
		debug[1] = 0.05 * h;
		debug[2] = 0.35 * w;
		debug[3] = 0.1 * w;

		endgame[0] = 0.1 * w;
		endgame[1] = 0.1 * h;
		endgame[2] = 0.8 * w;
		endgame[3] = 0.8 * h;
	}

	// Main Panel
	float main[4];

	// Hint Panel
	float hint[4];

	// Planet Panel
	float planet[4];

	// Debug Panel
	float debug[4];

	// Endgame Panel
	float endgame[4];
};