#include "engine/StaticMesh.hpp"
#include "engine/ResourceManager.hpp"
#include "engine/Renderer.hpp"

#include "lighting/LightManager.hpp"
#include "opengl/Shader.h"

#include "collision/CollisionManager.hpp"
#include "collision/BoundingSphere.hpp"

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"



// Default Constructor
StaticMesh::StaticMesh(const std::shared_ptr<Model>& model, const TransformLayout& transLayout, 
	const std::string& shaderName, const CollisionLayout& collisionLayout)
	: _model(model),
	_transformLayout(transLayout),
	_shader(ResourceManager::Get().GetShader(shaderName)),
	_modelMatrix(glm::mat4(1.0f)),
	_boundingSphere(std::make_shared<BoundingSphere>(collisionLayout))
{
	// Translate the mesh to the correct location
	Translate(_transformLayout.Location());
	Rotate(_transformLayout.Rotation());
	Scale(_transformLayout.Scale());
}

// Constructor with one mesh
StaticMesh::StaticMesh(const std::shared_ptr<Mesh>& mesh, const TransformLayout& transLayout, 
	const std::string& shaderName, const CollisionLayout& collisionLayout)
	: _model(std::make_shared<Model>(mesh)),
	_transformLayout(transLayout),
	_shader(ResourceManager::Get().GetShader(shaderName)),
	_modelMatrix(glm::mat4(1.0f)),
	_boundingSphere(std::make_shared<BoundingSphere>(collisionLayout))
{
	// Translate the mesh to the correct location
	Translate(_transformLayout.Location());
	Rotate(_transformLayout.Rotation());
	Scale(_transformLayout.Scale());
}

// Constructor with multiples meshes
StaticMesh::StaticMesh(const std::vector<std::shared_ptr<Mesh>>& meshes, const TransformLayout& transLayout, 
	const std::string& shaderName, const CollisionLayout& collisionLayout)
	: _model(std::make_shared<Model>(meshes)),
	_transformLayout(transLayout),
	_shader(ResourceManager::Get().GetShader(shaderName)),
	_modelMatrix(glm::mat4(1.0f)),
	_boundingSphere(std::make_shared<BoundingSphere>(collisionLayout))
{
	// Translate the mesh to the correct location
	Translate(_transformLayout.Location());
	Rotate(_transformLayout.Rotation());
	Scale(_transformLayout.Scale());
}


void StaticMesh::Draw(bool isParticuleInstance, int countParticule)
{
	SendUniforms();
	_model->Draw(_shader, isParticuleInstance, countParticule);
}

/*
* Transfromations
*/

void StaticMesh::ApplyTransforms()
{ 
	_modelMatrix = glm::mat4(1.0f);
	_boundingSphere->applyTransforms();
}


void StaticMesh::Scale(float alpha)
{
	_modelMatrix = _modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(alpha));
	
	// Bouding Sphere
	_boundingSphere->scale(alpha);
	updateBoundingSphere();
}

void StaticMesh::Translate(const glm::vec3& delta)
{
	_modelMatrix = _modelMatrix * glm::translate(glm::mat4(1.0f), delta);

	// Bouding Sphere
	_boundingSphere->translate(delta);
	updateBoundingSphere();
}

void StaticMesh::Rotate(const glm::vec3& alpha)
{
	_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(alpha.x), glm::vec3(1, 0, 0));
	_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(alpha.y), glm::vec3(0, 1, 0));
	_modelMatrix *= glm::rotate(glm::mat4(1.0f), glm::radians(alpha.z), glm::vec3(0, 0, 1));
}

void StaticMesh::updateBoundingSphere()
{
	// Remove bounding sphere inside all the cases where the sphere was
	_collisionManagerPtr->DeleteSphere(_boundingSphere);
	_collisionManagerPtr->AddSphere(_boundingSphere);
}

void StaticMesh::disableBoundingBox()
{
	_collisionManagerPtr->DeleteSphere(_boundingSphere);
}




/*
* Uniforms
*/
void StaticMesh::SendUniforms()
{
	_shader->Bind();

	// UV 
	_shader->SetUniform1f("uvScale", 1.0f);

	// Send Transformations Matrixes
	Renderer::Get().SendTransMatrixUniforms(GetModelMatrix(), _shader);

	// Send Lights
	LightManager::Get().SendUniforms(_shader);

	_shader->Unbind();
}

/*
* Static Data
*/
CollisionManager* StaticMesh::_collisionManagerPtr = nullptr;

void StaticMesh::SetCollisionManagerPtr(CollisionManager* cm_Ptr)
{
	_collisionManagerPtr = cm_Ptr;
}

/*
* Free Memory of model
*/
void StaticMesh::Free()
{
	_model->Free();
}

