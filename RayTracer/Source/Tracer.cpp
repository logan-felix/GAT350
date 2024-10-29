#include "Tracer.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Scene.h"

color3_t Tracer::Trace(Scene& scene, const ray_t& ray, float minDistance, float maxDistance)
{
	raycastHit_t raycastHit;
	float closestDistance = maxDistance;
	bool isHit = false;

	// check for object hit in scene
	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray, raycastHit, minDistance, closestDistance))
		{
			isHit = true;
			closestDistance = raycastHit.distance;
		}
	}

	if (isHit)
	{
		color3_t attenuation;
		ray_t scatter;
		if (raycastHit.material.lock()->Scatter(ray, raycastHit, attenuation, scatter))
		{
			return attenuation * Trace(scene, scatter, minDistance, maxDistance);
		}
	}

	// sky
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	color3_t color = Lerp(color3_t{ 1, 1, 1 }, color3_t{ 0.5f, 0.7f, 1.0f }, t);

	return color;
}
