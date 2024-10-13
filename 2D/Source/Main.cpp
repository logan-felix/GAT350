#include "Renderer.h"
#include "Framebuffer.h"
#include "MathUtils.h"
#include "PostProcess.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Image image;
    image.Load("scenic.jpg");


    int fbWidth = 800;
    int fbHeight = 600;
    Framebuffer framebuffer(renderer, fbWidth, fbHeight);

    bool quit = false;
    while (!quit)
    {
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

        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

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

        /*int mx, my;
        SDL_GetMouseState(&mx, &my);

        framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 0, 255, 255 });
        framebuffer.DrawQuadraticCurve(100, 200, 200, 100, 300, 200, { 255, 0, 255, 255 });
        framebuffer.DrawCubicCurve(150, 200, 150, 50, mx, my, 300, 200, { 255, 0, 255, 255 });

        int ticks = SDL_GetTicks();
        float time = ticks * 0.001f;
        float t = std::abs(std::sin(time));
        int x, y;
        CubicPoint(150, 200, 150, 50, mx, my, 300, 200, t, x, y);
        framebuffer.DrawRect(x, y, 10, 10, { 0, 255, 0, 255 });*/

        framebuffer.DrawImage(0, 0, image);

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

        framebuffer.Update();

        renderer = framebuffer;
        //renderer.CopyFramebuffer(framebuffer);

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }

	return 0;
}