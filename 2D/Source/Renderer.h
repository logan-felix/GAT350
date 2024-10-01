#pragma once
#include <SDL.h>

class Renderer
{
public:
	bool Initialize();
	bool CreateWindow();

private:
	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
};