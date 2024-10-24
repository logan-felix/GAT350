#pragma once
#include "SceneObject.h"
#include "Ray.h"
#include "Material.h"
#include <glm/glm.hpp>

class Sphere : public SceneObject
{
public:
	Sphere() = default;
	Sphere(const glm::vec3& center, float radius, std::shared_ptr<Material> material) :
		SceneObject{ material },
		m_center{ center },
		m_radius { radius }
	{}

	bool Hit(const ray_t& ray) override;

private:
	glm::vec3 m_center{ 0 };
	float m_radius{ 0 };
};