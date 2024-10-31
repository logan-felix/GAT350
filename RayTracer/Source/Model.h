#pragma once
#include "Color.h"
#include "SceneObject.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model
{
public:
	Model() = default;
	Model(const vertices_t& vertices, const color_t& color) : m_vertices{ vertices }, m_color{ color } {}

	bool Load(const std::string& filename);
	void Draw(class Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera);

	void SetColor(const color_t& color) { m_color = color; }

private:
	vertices_t m_vertices;
	color_t m_color;
};