#include "SDL2/SDL.h"
#include <iostream>

// 计时器回调函数
Uint32 timerCallback(Uint32 interval, void *param) {
    std::cout << "计时器触发! 参数: " << (char *)param << std::endl;
    return interval; // 返回相同间隔继续计时，返回0停止计时器
}

#undef main
int main() {
    SDL_Init(SDL_INIT_TIMER);

    // 创建计时器：1000ms间隔，传递参数
    const char *message = "Hello Timer!";
    SDL_TimerID timerID = SDL_AddTimer(1000, timerCallback, (void *)message);

    if (timerID == 0) {
        std::cout << "创建计时器失败: " << SDL_GetError() << std::endl;
        return -1;
    }
    for (int i = 0; i < 5; ++i) 
        std::cout << "计时器已创建，ID: " << timerID << std::endl;

    // 让程序运行5秒
    SDL_Delay(5000);

    // 移除计时器
    SDL_RemoveTimer(timerID);

    SDL_Quit();
    return 0;
}
