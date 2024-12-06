#include "FragmentShader.h"
#include "Shader.h"

color4_t FragmentShader::Process(const fragment_input_t& fragment)
{
	// Point Light
	glm::vec3 light_position = Shader::uniforms.view * glm::vec4{ Shader::uniforms.light.position, 1 };
	glm::vec3 light_dir = glm::normalize(light_position - fragment.position);

	// Directional Light
	//light_dir = glm::normalize(Shader::uniforms.view * glm::vec4{ -Shader::uniforms.light.direction, 0 });

	// Diffuse
	float intensity = std::max(0.0f, glm::dot(light_dir, fragment.normal));
	color3_t diffuse = Shader::uniforms.light.color * intensity;

	// Specular
	color3_t specular = color3_t{ 0 };
	if (intensity > 0)
	{
		glm::vec3 reflection = glm::reflect(-light_dir, fragment.normal);
		glm::vec3 view_dir = glm::normalize(-fragment.position);
		intensity = std::max(0.0f, glm::dot(reflection, view_dir));
		intensity = std::pow(intensity, Shader::uniforms.material.shininess);
		specular = Shader::uniforms.material.specular * intensity;
	}

	color3_t color = (Shader::uniforms.ambient + diffuse) * Shader::uniforms.material.albedo + specular;

	return color4_t{ color, 1 };
}


