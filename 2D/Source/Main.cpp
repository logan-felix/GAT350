#include "Renderer.h"
#include "Framebuffer.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    int fbWidth = 400;
    int fbHeight = 300;
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

        //clear screen
        //SDL_SetRenderDrawColor(renderer.m_renderer, 0, 0, 0, 0);
        //SDL_RenderClear(renderer.m_renderer);


        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

        //for (int i = 0; i < 10; i++)
        //{
        //    int x = rand() % fbWidth;
        //    int y = rand() % fbHeight;
        //    int x2 = rand() % fbWidth;
        //    int y2 = rand() % fbHeight;
        //    int x3 = rand() % fbWidth;
        //    int y3 = rand() % fbHeight;
        //    //framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });
        //    //framebuffer.DrawRect(10, 10, 50, 25, { 0, 255, 0, 255 });
        //    //framebuffer.DrawLine(x, y, x2, y2, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), 255});
        //    framebuffer.DrawTriangle(x, y, x2, y2, x3, y3, { 0, 255, 0, 255 });
        //}

        framebuffer.DrawCircle(100, 100, 40, { 255, 0, 0, 255 });
        framebuffer.DrawTriangle(200, 200, 250, 250, 150, 270, { 0, 255, 0, 255 });
        framebuffer.DrawLine(300, 100, 350, 250, { 255, 255, 0, 255 });

        framebuffer.Update();

        renderer = framebuffer;
        //renderer.CopyFramebuffer(framebuffer);

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }

	return 0;
}