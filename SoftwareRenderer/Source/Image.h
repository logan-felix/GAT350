#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>

using color_t = SDL_Color;

class Image
{
public:
	Image() = default;
	~Image() = default;

	bool Load(const std::string& filename);

public:
	int m_width{ 0 };
	int m_height{ 0 };

	std::vector<color_t> m_buffer;
};