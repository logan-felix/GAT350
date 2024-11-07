#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Tracer.h"
#include "ETime.h"
#include <iostream>

void Scene::Update()
{
	for (auto& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render(Framebuffer& framebuffer, const Camera& camera, int numSamples, int depth)
{
	Time frameTimer;
	Time scanlineTimer;

	/*float timeEst = 0;
	int timeEstMin = 0;
	int timeEstSec = 0;
	float avgScanlineTime = 0;
	float totalScanlineTime = 0;*/

	for (int y = 0; y < framebuffer.m_height; y++)
	{
		scanlineTimer.Reset();
		for (int x = 0; x < framebuffer.m_width; x++)
		{
			color3_t color{ 0 };

			for (int i = 0; i < numSamples; i++)
			{
				glm::vec2 pixel{ x,y };
				glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width, framebuffer.m_height };
				point.y = 1 - point.y;

				ray_t ray = camera.GetRay(point);
				color += Tracer::Trace(*this, ray, 0.001f, 100.0f, depth);
			}
			color = color / (float)numSamples;
			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}

		/*totalScanlineTime += scanlineTimer.GetElapsedTime();
		avgScanlineTime = totalScanlineTime / (y + 1);
		timeEst = avgScanlineTime * (framebuffer.m_height - (y + 1));

		timeEstMin = (int)timeEst / 60;
		timeEstSec = (int)timeEst % 60;*/

		std::cout << "y: " << y << " - " << scanlineTimer.GetElapsedTime() << std::endl;
		//std::cout << "Time estimate: " << timeEstMin << " min, " << timeEstSec << " sec" << std::endl;
	}
	std::cout << "frame time: " << frameTimer.GetElapsedTime() << std::endl;
}
