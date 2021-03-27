#pragma once

#include "engine/Model.hpp"
#include "opengl/Shader.h"
#include "collision/CollisionLayout.hpp"

#include <string>
#include <memory>
#include <functional>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Fog;
class CollisionManager;
class BoundingSphere;

class TransformLayout
{
public:
	TransformLayout(const glm::vec3& loc, const glm::vec3& rot = glm::vec3(0, 0, 0), float scale = 1.0f, float uvScale = 1.0f)
		: _location(loc), _rotation(rot), _scale(scale), _uvScale(uvScale) {}

	glm::vec3 Location() const { return _location; }
	glm::vec3 Rotation() const { return _rotation; }
	float Scale() const { return _scale; }
	float UvScale() const { return _uvScale; }

private:
	glm::vec3 _location;
	glm::vec3 _rotation;
	float _scale;
	float _uvScale;
};



class StaticMesh
{
public:
	// Constructor
	StaticMesh(const Model& model, const TransformLayout& transLayout, const std::string& shaderName = "Default", 
		const CollisionLayout& collisionLayout = CollisionLayout());

	void Draw(bool isParticuleInstance = false, int countParticule = 0);

	glm::mat4 GetModelMatrix() const { return _modelMatrix; }
	std::shared_ptr<Shader>& GetShader() { return _shader; }

	void Translate(const glm::vec3& delta);
	void Scale(float alpha);
	void Rotate(const glm::vec3& alpha);

	void updateBoundingSphere();
	void disableBoundingBox();
	
	unsigned int GetVAO() const { return _model.GetVAO(); }

	void Free();

	static void SetCollisionManagerPtr(CollisionManager* cm_Ptr);

private:
	void SendUniforms();

	Model _model;

	TransformLayout _transformLayout;
	std::shared_ptr<Shader> _shader;
	glm::mat4 _modelMatrix;
	
	std::shared_ptr<BoundingSphere> _boundingSphere;

	static CollisionManager* _collisionManagerPtr;

};