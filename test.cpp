#include "stdc++.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Centered Player", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    float worldX = 100.0f, worldY = 100.0f;
    float cameraX = 0.0f, cameraY = 0.0f;

    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = 1;
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_UP:
                    worldY -= 10;
                    break;
                case SDLK_DOWN:
                    worldY += 10;
                    break;
                case SDLK_LEFT:
                    worldX -= 10;
                    break;
                case SDLK_RIGHT:
                    worldX += 10;
                    break;
                }
            }
        }

        // 更新相机
        cameraX = worldX - SCREEN_WIDTH / 2;
        cameraY = worldY - SCREEN_HEIGHT / 2;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // 绘制背景网格（示例）
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        for (int x = -(int)cameraX % 50; x < SCREEN_WIDTH; x += 50)
            SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
        for (int y = -(int)cameraY % 50; y < SCREEN_HEIGHT; y += 50)
            SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);

        // 绘制玩家（始终在屏幕中间）
        SDL_Rect playerRect = {SCREEN_WIDTH / 2 - 16, SCREEN_HEIGHT / 2 - 16,
                               32, 32};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_RenderPresent(renderer);
        // SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}