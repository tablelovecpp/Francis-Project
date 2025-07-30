#define USE_MY_LIB
#include "ammo.h"
#include "button.h"
#include "camera.h"
#include "stdc++.h"
#include "triangle.h"

using namespace std;
#define def auto

// 窗口尺寸
def WIN_WIDTH = get_window_size().cx / 2, WIN_HEIGHT = get_window_size().cy / 2;

SDL_Renderer *renderer;                                              // 渲染器
SDL_Window *window;                                                  // 窗口
def startButton = new Button(WIN_WIDTH / 2, WIN_HEIGHT / 2, 50, 50); // 启动按钮

// 镜头
Camera camera = Camera_Create(WIN_WIDTH, WIN_HEIGHT);

// 炮台位置
CameraObject player = {.worldX = (float)WIN_WIDTH / 2,
                       .worldY = (float)WIN_HEIGHT / 2};

// 玩家移动的计时器
def player_tick = (Uint32)0;

// 玩家移动
def playerMove() {
    if (SDL_GetTicks() - player_tick > 50) {
        player_tick = SDL_GetTicks();
        if (KeyDown('W'))
            player.worldY -= 10;
        if (KeyDown('S'))
            player.worldY += 10;
        if (KeyDown('A'))
            player.worldX -= 10;
        if (KeyDown('D'))
            player.worldX += 10;
    }
}

// 初始化
def init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        SDL_GetError();
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    startButton->SetRenderer(renderer);
    // cout << SDL_GetWindowID(window);
}

// 处理事件
def handleEvent() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // 检测退出事件
        if (event.type == SDL_QUIT) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            // SDL_RemoveTimer(ammo_timer);
            SDL_Quit();
            exit(0);
        }

        // 处理按钮事件
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

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);

        if (handleEvent())
            break;
    }
}

// 进入游戏后的处理
def toGame() {
    // 设置标题
    SDL_SetWindowTitle(window, "版本: 内测版");

    while (1) {
        SDL_RenderClear(renderer);

        // 获取鼠标的角度
        int x = 0, y = 0;
        SDL_GetMouseState(&x, &y);

        // 更新炮台的位置
        playerMove();
        Camera_LookAt(&camera, &player);
        def pos = Camera_WorldToScreen(&camera, &player, 0, 0);

        // 画出炮台
        int circle_r = 10;
        SDL_DrawCircle(renderer, pos.x, pos.y, circle_r, {0, 0, 0, 255});

        // 画出炮管
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // 计算角度并控制长度
        double angle = atan2(y - pos.y, x - pos.x);
        int endX = pos.x + 20 * cos(angle), endY = pos.y + 20 * sin(angle);

        thickLineRGBA(renderer, WIN_WIDTH / 2, WIN_HEIGHT / 2, endX, endY, 3, 0,
                      0, 0, 255);
        // 画出子弹
        updateAmmo();
        drawAmmo();

        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // SDL_UpdateWindowSurface(window);

        // 测试区
        // cout << 1;
        cout << "x: " << player.worldX << " y: " << player.worldY << endl;

        if (handleEvent())
            break;
    }
}

#undef main
int main() {
    // 初始化函数
    init();
    // 进入开始界面
    toStart();
    // 进入游戏界面
    toGame();
    // 返回0，表示程序正常结束
    return 0;
}