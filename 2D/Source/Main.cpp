#include "Renderer.h"
#include "Framebuffer.h"

#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Framebuffer framebuffer(renderer, 100, 75);

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

        for (int i = 0; i < 100; i++)
        {
            int x = rand() % 100;
            int y = rand() % 75;
            framebuffer.DrawPoint(x, y, { 255, 255, 255, 255 });
        }

        framebuffer.DrawRect(10, 10, 50, 25, { 0, 255, 0, 255 });

        framebuffer.Update();

        renderer = framebuffer;
        //renderer.CopyFramebuffer(framebuffer);

        // show screen
        SDL_RenderPresent(renderer.m_renderer);
    }

	return 0;
}