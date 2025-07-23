#include "rotate.h"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("旋转功能示例", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    bool running = true;
    SDL_Event e;
    int mouseX = 400, mouseY = 300;
    
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            } else if (e.type == SDL_MOUSEMOTION) {
                mouseX = e.motion.x;
                mouseY = e.motion.y;
            }
        }
        
        // 更新旋转角度（每帧旋转2度）
        RotationUtils::updateRotation(2.0f);
        
        // 计算旋转后的位置
        SDL_Point rotatedPos = RotationUtils::getRotatedPosition(mouseX, mouseY, 80.0f);
        
        // 清屏
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // 绘制鼠标中心点
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawPoint(renderer, mouseX, mouseY);
        
        // 绘制旋转的图形
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int i = -5; i <= 5; i++) {
            for (int j = -5; j <= 5; j++) {
                if (i*i + j*j <= 25) {
                    SDL_RenderDrawPoint(renderer, rotatedPos.x + i, rotatedPos.y + j);
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
