#define USE_MY_LIB
#include "button.h"
#include "player.h"
#include "stdc++.h"
#include "triangle.h"

using namespace std;
#define def auto

// 窗口尺寸
def WIN_WIDTH = get_window_size().cx / 2, WIN_HEIGHT = get_window_size().cy / 2;

SDL_Renderer *renderer; // 渲染器
SDL_Window *window;     // 窗口
auto startButton =
    new Button(WIN_WIDTH / 2, WIN_HEIGHT / 2, 50, 50); // 启动按钮

// 初始化
def init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        SDL_GetError();
    TTF_Init();
    window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    startButton->SetRenderer(renderer);
}

// 处理事件
def handleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }
        if (startButton->handleEvent(&event) && startButton != NULL) {
            startButton->clearButton();
            return true;
        } else if (startButton == NULL)
            return false;
    }
    return false;
}

// 未进入游戏前的处理
def toStart() {
    while (1) {
        SDL_RenderClear(renderer);
        startButton->render(true);

        // 画出按钮上的三角形(暂封)
        // def _pos = startButton->getButtonPosition();
        // def _size = startButton->getButtonSize();
        // _size.cx -= 20, _size.cy -= 20;
        // float px = _pos.cx, py = _pos.cy;
        // SDL_Vertex vertices[3] = {
        //     {{px - _size.cx / 2, py + _size.cy / 2}, {255, 255, 255, 0}},
        //     {{px, py - _size.cy / 2}, {255, 255, 255, 0}},
        //     {{px + _size.cx / 2, py + _size.cy / 2}, {255, 255, 255, 0}}};
        // def triangle = SDL_Triangle(vertices[0], vertices[1], vertices[2]);
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Render_Triangle(renderer, triangle);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);

        if (handleEvent())
            break;
    }
}

// 进入游戏后的处理
def toGame() {
    SDL_SetWindowTitle(window, "版本: 内测版");
    while (1) {
        SDL_RenderClear(renderer);

        // 获取鼠标的角度
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);

        // 画出炮台
        int circle_r = 10;
        SDL_DrawCircle(renderer, WIN_WIDTH / 2, WIN_HEIGHT / 2, circle_r,
                       {0, 0, 0, 255});

        // 画出炮管
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // 计算角度并控制长度
        double angle = atan2(y - WIN_HEIGHT / 2, x - WIN_WIDTH / 2);
        int endX = WIN_WIDTH / 2 + 50 * cos(angle);
        int endY = WIN_HEIGHT / 2 + 50 * sin(angle);

        thickLineRGBA(renderer, WIN_WIDTH / 2, WIN_HEIGHT / 2, endX, endY, 3, 0,
                      0, 0, 255);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
        // SDL_UpdateWindowSurface(window);

        if (handleEvent())
            break;
    }
}

#undef main
int main() {
    init();
    toStart();
    toGame();
    return 0;
}