#include "hud/PannelUI.hpp"
#include "opengl/Mesh.hpp"
#include "engine/ResourceManager.hpp"
#include "glm/gtx/transform.hpp"


PanelUI::PanelUI(const std::string& path, const std::string& name, float x, float y, float scale)
	: _modelMatrix(glm::mat4(1.0f)), _name(name)
{
	// Load Texture
	float imgWidth = 0.0f, imgHeight = 0.0f;
	try {
		imgWidth = ResourceManager::Get().LoadTexture(path, DIFFUSE).Width();
		imgHeight = ResourceManager::Get().LoadTexture(path, DIFFUSE).Height();
	}
	catch (const std::string& e) {
		std::cerr << e << std::endl;
	}
	
	float posX = imgWidth / 1280.0;
	float posY = imgHeight / 720.0;
	
	std::vector<ShapeVertex> vertices = {
		// position								  // normal				      // texcoord
		ShapeVertex(glm::vec3(-posX, posY, 0.0),  glm::vec3(0.0, 0.0, 0.0),   glm::vec2(0.0, 0.0)),
		ShapeVertex(glm::vec3(posX, posY, 0.0),   glm::vec3(0.0, 0.0, 0.0),   glm::vec2(1.0, 0.0)),
		ShapeVertex(glm::vec3(posX,-posY, 0.0),   glm::vec3(0.0, 0.0, 0.0),   glm::vec2(1.0, 1.0)),
		ShapeVertex(glm::vec3(-posX,-posY, 0.0),  glm::vec3(0.0, 0.0, 0.0),   glm::vec2(0.0, 1.0))
	};

	auto material = ResourceManager::Get().CacheBasicMaterial(name, path);

	std::vector<unsigned int> indices = {
		0,1,3,
		1,3,2
	};

	Mesh newMesh = Mesh(vertices, material, indices);
	_mesh = std::make_shared<Mesh>(newMesh);

	ComputeModelMatrix(x, y, scale);
}

void PanelUI::Draw() const {
	auto shader = ResourceManager::Get().GetShader("PanelUI");

	shader->Bind();
	shader->SetUniformMatrix4fv("uModelMatrix", _modelMatrix);

	_mesh->Draw(shader);
}

void PanelUI::ComputeModelMatrix(float x, float y, float scale)
{
	Scale(scale);
	Translate(x, y);
}


void PanelUI::Scale(float alpha)
{
	_modelMatrix = glm::scale(_modelMatrix, glm::vec3(alpha, alpha, 1));
}

void PanelUI::Translate(float x, float y)
{
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(x, y, 0));
}

void PanelUI::Place(float x, float y)
{
	_modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
}

void PanelUI::Free()
{ 
	_mesh->Free(); 
}
