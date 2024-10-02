#pragma once
#include <SDL.h>
#include <iostream>

class Renderer
{
public:
	bool Initialize();
	bool CreateWindow(std::string windowName, int width, int height);
	void CopyFramebuffer(const class Framebuffer& framebuffer);

	void operator = (const class Framebuffer& framebuffer);

public:
	int m_width = 0;
	int m_height = 0;

	SDL_Renderer* m_renderer{ nullptr };
	SDL_Window* m_window{ nullptr };
};