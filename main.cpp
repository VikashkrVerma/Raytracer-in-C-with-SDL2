#include "dataStructures.h"
#include "trig.h"
#include "Utilities.h"
#include <fstream>
#include <SDL2/SDL.h>
#include <math.h>

SDL_Surface *screen;
SDL_Event event;
SDL_Renderer* renderer; // Declare the renderer globally

void calculate_image(void)
{
    color c;
    Ray ray;
    Uint32 sdl_color;
    Uint32 *pixmem32 = new Uint32[ImageW * ImageH]; // Create pixel buffer

    for (int i = ImageH - 1; i >= 0; --i)
    {
        for (int j = ImageW - 1; j >= 0; --j)
        {
            ray = convertToRay(i, j);
            c = rayTrace(ray, 0);
            c.scale();

            // Create pixel color
            sdl_color = (Uint8)(0xFF * c.b) << 16 | (Uint8)(0xFF * c.g) << 8 | (Uint8)(0xFF * c.r);

            // Store pixel in pixel buffer
            pixmem32[i * ImageW + j] = sdl_color;
        }
    }

    // Create a texture from the pixel buffer
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, ImageW, ImageH);
    SDL_UpdateTexture(texture, NULL, pixmem32, ImageW * sizeof(Uint32));

    // Clear the renderer and copy the texture to the renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Clean up
    delete[] pixmem32;
    SDL_DestroyTexture(texture);
}

void deleteGlobals()
{
    if (g_patLightList != 0)
    {
        delete[] g_patLightList;
    }
    if (g_papoObjects != 0)
    {
        for (int i = 0; i < g_iNumPlanes + g_iNumSpheres; ++i)
        {
            delete g_papoObjects[i];
        }
        delete[] g_papoObjects;
    }
}

void run()
{
    bool running = true;

    calculate_image(); // Call calculate_image to draw the image

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ImageW, ImageH, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // Assign renderer globally

    if (argc > 1)
    {
        readInGlobals(argv[1]);
    }
    else
    {
        readInGlobals("source.dat");
    }

    run();

    deleteGlobals();
    SDL_DestroyRenderer(renderer); // Cleanup renderer
    SDL_DestroyWindow(window); // Cleanup window
    SDL_Quit(); // Cleanup SDL
    return 0;
}
