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
#include "Triangle.h"
#include "Color.h"

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void InitScene(Scene& scene);
void InitCornellBox(Scene& scene, Camera& camera);

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    // initialize
    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("RayTracer", 1200, 675);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_height);

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
    camera.SetView({ -10, 8, -20 }, { 0, 0, -5 });

    Scene scene;
    InitScene(scene);
    //InitCornellBox(scene, camera);
    
    scene.Update();
    scene.Render(framebuffer, camera, 200, 6);
    framebuffer.Update();

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

        renderer.CopyFramebuffer(framebuffer);
        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }

	return 0;
}

void InitScene(Scene& scene)
{
    //scene.SetSky(HSVtoRGB(240, 1, 0.2f), HSVtoRGB(240, 1, 1));

    std::shared_ptr<Material> lightgray = std::make_shared<Metal>(color3_t{ 0.75f }, 0.1f);
    std::shared_ptr<Material> gray = std::make_shared<Lambertian>(color3_t{ 0.5f });
    std::shared_ptr<Material> white = std::make_shared<Dielectric>(color3_t{ 1 }, 1.333f);
    std::shared_ptr<Material> whiteMetal = std::make_shared<Metal>(color3_t{ 1 }, 0.1f);
    std::shared_ptr<Material> red = std::make_shared<Metal>(color3_t{ 1, 0, 0 }, 0.0f);
    std::shared_ptr<Material> yellow = std::make_shared<Dielectric>(color3_t{ 1, 1, 0 }, 1.333f);
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
    std::shared_ptr<Material> cyan = std::make_shared<Lambertian>(color3_t{ 0, 1, 1 });
    std::shared_ptr<Material> blue = std::make_shared<Dielectric>(color3_t{ 0.5f, 0.5f, 1 }, 0.75f);
    std::shared_ptr<Material> magenta = std::make_shared<Dielectric>(color3_t{ 1, 0, 1 }, 1.333f);

    /*std::vector<std::shared_ptr<Material>> materials;
    materials.push_back(gray);
    materials.push_back(grayMetal);
    materials.push_back(white);
    materials.push_back(red);
    materials.push_back(yellow);
    materials.push_back(green);
    materials.push_back(cyan);
    materials.push_back(blue);
    materials.push_back(magenta);*/

    std::unique_ptr<Model> cube = std::make_unique<Model>(Transform{ glm::vec3{ 5, 2, -15 }, glm::vec3{ 0, 40, 0 }, glm::vec3{ 4 } }, blue);
    cube->Load("Models/cube.obj");
    scene.AddObject(std::move(cube));

    std::unique_ptr<Plane> plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1 } }, gray);
    scene.AddObject(std::move(plane));

    std::unique_ptr<Triangle> triangle = std::make_unique<Triangle>
        (
            glm::vec3{ -12, 10, 24 },
            glm::vec3{ 0, 7, 21 },
            glm::vec3{ -6, 1, 18 },
            green
        );
    scene.AddObject(std::move(triangle));

    for (int i = 0; i < 100; i++)
    {
        float random_radius = randomf(0.5f, 3.0f);
        std::shared_ptr<Material> random_material;
        switch (random(0, 4))
        {
        case 0:
            random_material = std::make_shared<Metal>(color3_t{ randomf(0, 1), randomf(0, 1), randomf(0, 1) }, randomf(0, 1));
            break;
        case 1:
            random_material = std::make_shared<Emissive>(color3_t{ randomf(0, 1), randomf(0, 1), randomf(0, 1) }, randomf(1, 2));
            break;
        case 2:
            random_material = std::make_shared<Dielectric>(color3_t{ randomf(0, 1), randomf(0, 1), randomf(0, 1) }, randomf(0.5f, 1.333f));
            break;
        case 3:
            random_material = std::make_shared<Lambertian>(color3_t{ randomf(0, 1), randomf(0, 1), randomf(0, 1) });
            break;
        }
        auto sphere = std::make_unique<Sphere>(Transform{ random({-20, 1, -20}, {20, 1, 20}) }, 1.0f, random_material);
        scene.AddObject(std::move(sphere));
    }

    auto sphere = std::make_unique<Sphere>(Transform{ glm::vec3{5, 5, 0} }, 5, lightgray);
    scene.AddObject(std::move(sphere));
}

void InitCornellBox(Scene& scene, Camera& camera)
{
    camera.SetFOV(20.0f);

    std::shared_ptr<Material> gray = std::make_shared<Metal>(color3_t{ 0.5f }, 0.1f);
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 1 });
    std::shared_ptr<Material> whiteEmissive = std::make_shared<Emissive>(color3_t{ 1 }, 15.0f);
    std::shared_ptr<Material> red = std::make_shared<Lambertian>(HSVtoRGB(354, 0.9f, 0.64f));
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(HSVtoRGB(132, 0.9f, 0.3f));
    std::shared_ptr<Material> glass = std::make_shared<Dielectric>(color3_t{ 0.5f, 0.5f, 1 }, 1.333f);

    // white ceiling
    std::unique_ptr<Plane> ceiling = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 50, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1 } }, white);
    // light
    std::unique_ptr<Model> light = std::make_unique<Model>(Transform{ glm::vec3{ 0, 49, 20 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 15, 1, 15 } }, whiteEmissive);
    // green right wall
    std::unique_ptr<Plane> right = std::make_unique<Plane>(Transform{ glm::vec3{ 35, 0, 0 }, glm::vec3{ 0, 0, 90 }, glm::vec3{ 1 } }, green);
    // red left wall
    std::unique_ptr<Plane> left = std::make_unique<Plane>(Transform{ glm::vec3{ -35, 0, 0 }, glm::vec3{ 0, 0, 90 }, glm::vec3{ 1 } }, red);
    // white back wall
    std::unique_ptr<Plane> back = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 60 }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 1 } }, white);
    std::unique_ptr<Plane> wall = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, -60 }, glm::vec3{ 90, 0, 0 }, glm::vec3{ 1 } }, white);
    // white floor
    std::unique_ptr<Plane> floor = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1 } }, white);

    // cube
    std::unique_ptr<Model> cube = std::make_unique<Model>(Transform{ glm::vec3{ -10, 8, 40 }, glm::vec3{ 0, 60, 0 }, glm::vec3{ 16 } }, gray);
    // sphere
    std::unique_ptr<Model> sphere = std::make_unique<Model>(Transform{ glm::vec3{ 10, 6, 20 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 6 } }, glass);
    
    
    light->Load("Models/cube.obj");
    cube->Load("Models/cube.obj");
    sphere->Load("Models/sphere.obj");

    scene.AddObject(std::move(ceiling));
    scene.AddObject(std::move(light));
    scene.AddObject(std::move(right));
    scene.AddObject(std::move(left));
    scene.AddObject(std::move(back));
    scene.AddObject(std::move(wall));
    scene.AddObject(std::move(floor));

    scene.AddObject(std::move(cube));
    scene.AddObject(std::move(sphere));
}