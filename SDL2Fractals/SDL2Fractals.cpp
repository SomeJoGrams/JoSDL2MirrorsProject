// SDL2BaseVCPKG.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "SDL2BaseVCPKG.h"


int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "My SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL)
    {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Delay(3000);

    // ...

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
