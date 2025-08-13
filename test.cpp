#include "stdc++.h"
using namespace std;

#undef main
int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_SOFTWARE);

    while (1) {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
    
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {400, 300, 100, 100};
        SDL_RenderDrawRect(renderer, &rect);

        SDL_RenderDrawLine(renderer, 0, 300, 800, 300);
        SDL_RenderDrawLine(renderer, 400, 0, 400, 600);

        // if (SDL_GetTicks() % 1000 < 500
        // SDL_SetWindowTitle(window, "版本: 内测版");

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);
    }
    return 0;
}