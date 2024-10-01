#include <SDL.h>
#include <iostream>

#include "Renderer.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow();

	return 0;
}