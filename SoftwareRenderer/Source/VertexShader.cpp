#include "VertexShader.h"
#include "Shader.h"

//#define GOURAUD

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
	glm::mat4 mvp = Shader::uniforms.projection * Shader::uniforms.view * Shader::uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
	glm::mat4 mv = Shader::uniforms.view * Shader::uniforms.model;
	overtex.normal = glm::normalize(glm::mat3{ mv } * ivertex.normal);
	overtex.vposition = mv * glm::vec4{ ivertex.position, 1 };

#ifdef GOURAUD
	// Point Light
	/*glm::vec3 light_position = uniforms.view * glm::vec4{ uniforms.light.position, 1 };
	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	glm::vec3 light_dir = glm::normalize(light_position - vposition);*/

	// Directional Light
	glm::vec3 light_dir = glm::normalize(Shader::uniforms.view * glm::vec4{ -Shader::uniforms.light.direction, 0 });

	float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
	color3_t diffuse = Shader::uniforms.light.color * intensity;

	color3_t specular = color3_t{ 0 };
	if (intensity > 0)
	{
		glm::vec3 reflection = glm::reflect(-light_dir, ivertex.normal);
		glm::vec3 view_dir = glm::normalize(-ivertex.position);
		intensity = std::max(0.0f, glm::dot(reflection, view_dir));
		intensity = std::pow(intensity, Shader::uniforms.material.shininess);
		specular = Shader::uniforms.material.specular * intensity;
	}

	overtex.color = (Shader::uniforms.ambient + diffuse) * Shader::uniforms.material.albedo + specular;
#endif
}
