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
    renderer.CreateWindow("SoftwareRenderer", 800, 600);

    Input input;
    input.Initialize();
    input.Update();

    SetBlendMode(BlendMode::Normal);

    Camera camera(800, 600);
    camera.SetView(glm::vec3{ 0, 0, -50 }, glm::vec3{ 0 });
    camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ { 0, 0, -20 } };

    Image image;
    image.Load("space.jpg");

    Image imageAlpha;
    imageAlpha.Load("colors.png");
    PostProcess::Alpha(imageAlpha.m_buffer, 100);

    int fbWidth = 800;
    int fbHeight = 600;
    Framebuffer framebuffer(renderer, fbWidth, fbHeight);

    vertices_t vertices = { { -5, 5, 0 }, { 5, 5, 0 }, { -5, -5, 0 } };
    //Model model;
    std::shared_ptr<Model> teapotModel = std::make_shared<Model>();
    std::shared_ptr<Model> torusModel = std::make_shared<Model>();
    std::shared_ptr<Model> sphereModel = std::make_shared<Model>();

    teapotModel->Load("teapot.obj");
    torusModel->Load("torus.obj");
    sphereModel->Load("sphere.obj");

    std::vector<std::unique_ptr<Actor>> actors;

    Transform transform{ { -20, 0, -30 }, glm::vec3{0}, glm::vec3{2}};
    std::unique_ptr<Actor> teapot = std::make_unique<Actor>(transform, teapotModel);
    transform = { { 30, 0, 20 }, glm::vec3{0}, glm::vec3{5} };
    std::unique_ptr<Actor> torus = std::make_unique<Actor>(transform, torusModel);
    transform = { { 0, 0, 0 }, glm::vec3{0}, glm::vec3{3} };
    std::unique_ptr<Actor> sphere = std::make_unique<Actor>(transform, sphereModel);

    teapot->SetColor({ 100, 255, 100, 255 });
    torus->SetColor({ 255, 255, 100, 255 });
    sphere->SetColor({ 100, 100, 255, 255 });

    actors.push_back(std::move(teapot));
    actors.push_back(std::move(torus));
    actors.push_back(std::move(sphere));


    bool quit = false;
    while (!quit)
    {
        // update 
        time.Tick();
        input.Update();

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
        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

        framebuffer.DrawImage(0, 0, image);

        for (int i = 0; i < 1; i++)
        {
            int x = rand() % fbWidth;
            int y = rand() % fbHeight;
            int x2 = rand() % fbWidth;
            int y2 = rand() % fbHeight;
            int x3 = rand() % fbWidth;
            int y3 = rand() % fbHeight;
            //framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });
            //framebuffer.DrawRect(10, 10, 50, 25, { 0, 255, 0, 255 });
            //framebuffer.DrawLine(x, y, x2, y2, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), 255});
            //framebuffer.DrawTriangle(x, y, x2, y2, x3, y3, { 0, 255, 0, 255 });
            //framebuffer.DrawCircle(x, y, 20, { 255, 255, 255, 255 });
        }

        int mx, my;
        SDL_GetMouseState(&mx, &my);

        /*framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 0, 255, 255 });
        framebuffer.DrawQuadraticCurve(100, 200, 200, 100, 300, 200, { 255, 0, 255, 255 });
        framebuffer.DrawCubicCurve(150, 200, 150, 50, mx, my, 300, 200, { 255, 0, 255, 255 });*/

        //int x, y;
        //CubicPoint(150, 200, 150, 50, mx, my, 300, 200, t, x, y);
        //framebuffer.DrawRect(x, y, 10, 10, { 0, 255, 0, 255 });

#pragma region alpha_blend

        /*SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(0, 0, image);
        SetBlendMode(BlendMode::Multiply);
        framebuffer.DrawImage(mx, my, imageAlpha);*/

#pragma endregion

#pragma region post_process

        //PostProcess::Invert(framebuffer.m_buffer);
        //PostProcess::Monochrome(framebuffer.m_buffer);
        //PostProcess::ColorBalance(framebuffer.m_buffer, 100, 0, 100);
        //PostProcess::Brightness(framebuffer.m_buffer, 100);
        //PostProcess::Noise(framebuffer.m_buffer, 80);
        //PostProcess::Threshold(framebuffer.m_buffer, 100);
        //PostProcess::Posterize(framebuffer.m_buffer, 5);
        
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Edge(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height, 100);
        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::EmbossGrayscale(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

#pragma endregion

        glm::vec3 direction{ 0 };
        if (input.GetKeyDown(SDL_SCANCODE_W)) direction.z = 0.5f; // camera forward
        if (input.GetKeyDown(SDL_SCANCODE_S)) direction.z = -0.5f; // camera backward
        if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 0.5f; // camera right
        if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -0.5f; // camera left
        if (input.GetKeyDown(SDL_SCANCODE_SPACE)) direction.y = 0.5f; // camera up
        if (input.GetKeyDown(SDL_SCANCODE_LSHIFT)) direction.y = -0.5f; // camera down

        if (input.GetKeyDown(SDL_SCANCODE_UP)) cameraTransform.rotation.x -= 2; // look up
        if (input.GetKeyDown(SDL_SCANCODE_DOWN)) cameraTransform.rotation.x += 2; // look down
        if (input.GetKeyDown(SDL_SCANCODE_LEFT)) cameraTransform.rotation.y -= 2; // look left
        if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) cameraTransform.rotation.y += 2; // look right

        if (input.GetMouseButtonDown(2))
        {
            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;
        }
        else
        {
            input.SetRelativeMode(false);
        }

        glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

        cameraTransform.position += offset * 50.0f * time.GetDeltaTime();

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        /*cameraTransform.rotation.z += 90 * time.GetDeltaTime();
        model->Draw(framebuffer, cameraTransform.GetMatrix(), camera);*/

        for (auto& actor : actors)
        {
            actor->Draw(framebuffer, camera);
        }

        framebuffer.Update();

        renderer = framebuffer;
        //renderer.CopyFramebuffer(framebuffer);

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }

	return 0;
}