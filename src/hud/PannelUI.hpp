#pragma once

#include "glm/glm.hpp"
#include <string>
#include <memory>

class Mesh;

class PanelUI
{
public:
	PanelUI(const std::string& path, const std::string& name, float x = 0.0, float y = 0.0, float scale = 1.0);

	void Draw() const;

	inline bool IsVisible() const { return _visibility; };
	void setVisibility(bool visbility) { _visibility = visbility; };

	void Free();
	void Scale(float alpha);
	void Rotate(float alpha);
	void Translate(float x, float y);
	void Place(float x, float y);

private:
	void ComputeModelMatrix(float x, float y, float scale);

private:
	glm::mat4 _modelMatrix;
	std::shared_ptr<Mesh> _mesh;

	std::string _name;
	bool _visibility = false;
};