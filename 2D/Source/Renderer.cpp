#include "Renderer.h"
#include <iostream>

bool Renderer::Initialize()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Renderer::CreateWindow()
{
    // create window
    // returns pointer to window if successful or nullptr if failed
    m_window = SDL_CreateWindow("Game Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    // create renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    while (true)
    {
        // clear screen
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(m_renderer);

        // show screen
        SDL_RenderPresent(m_renderer);
    }

    return true;
}
