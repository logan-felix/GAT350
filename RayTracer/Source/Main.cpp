#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "PostProcess.h"
#include "Model.h"
#include "Transform.h"
#include "ETime.h"
#include "Input.h"
#include "Camera.h"
#include "Actor.h"
#include "Random.h"
#include "Tracer.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Color.h"

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(int argc, char* argv[])
{
    // initialize
    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("RayTracer", 800, 600);

    SetBlendMode(BlendMode::Normal);

    int fbWidth = 800;
    int fbHeight = 600;
    Framebuffer framebuffer(renderer, fbWidth, fbHeight);

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
    camera.SetView({ 0, 0, -20 }, { 0, 0, 0 });

    Scene scene;

    std::shared_ptr<Material> material = std::make_shared<Material>(color3_t{ 1, 0, 0 });

    std::shared_ptr<Material> gray = std::make_shared<Material>(color3_t{ 0.5f });
    std::shared_ptr<Material> red = std::make_shared<Material>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> yellow = std::make_shared<Material>(color3_t{ 1, 1, 0 });
    std::shared_ptr<Material> green = std::make_shared<Material>(color3_t{ 0, 1, 0 }); 
    std::shared_ptr<Material> cyan = std::make_shared<Material>(color3_t{ 0, 1, 1 });
    std::shared_ptr<Material> blue = std::make_shared<Material>(color3_t{ 0, 0, 1 });
    std::shared_ptr<Material> magenta = std::make_shared<Material>(color3_t{ 1, 0, 1 });

    std::vector<std::shared_ptr<Material>> materials;
    materials.push_back(gray);
    materials.push_back(red); 
    materials.push_back(yellow);
    materials.push_back(green); 
    materials.push_back(cyan); 
    materials.push_back(blue);
    materials.push_back(magenta);

    for (int i = 0; i < 10; i++)
    {
        float random_radius = randomf(0.5f, 2.0f);
        auto random_material = materials[random(1, materials.size() - 1)];
        auto object = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), random_radius, random_material);
        scene.AddObject(std::move(object));
    }

    std::unique_ptr<Plane> plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, gray); 
    scene.AddObject(std::move(plane)); 

    bool quit = false;
    while (!quit)
    {
        // update 
        time.Tick();

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }

        // render
        framebuffer.Clear(ColorConvert(color3_t{ 0.25f, 1.0f, 0.25f }));

        scene.Render(framebuffer, camera);

        framebuffer.Update();

        renderer.CopyFramebuffer(framebuffer);
        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }

	return 0;
}