#define USE_MY_LIB
#include "ammo.h"
#include "button.h"
#include "camera.h"
#include "enemy.h"
#include "stdc++.h"
#include "ttf.h"

// #include "triangle.h"

using namespace std;
#define def auto

// 窗口尺寸
def WIN_WIDTH = get_window_size().cx / 2, WIN_HEIGHT = get_window_size().cy / 2;

// 此时此刻游戏的状态
def IN_GAME = false; // 是否进入游戏(相当于点击了按钮之后的情况)

SDL_Renderer *renderer; // 渲染器
SDL_Window *window;     // 窗口
// def startButton = new

// 镜头
Camera camera = Camera_Create(WIN_WIDTH, WIN_HEIGHT);

// 炮台位置
CameraObject player = {.worldX = (float)0, .worldY = (float)0};

// 玩家移动的计时器
def player_tick = (Uint32)0;

// 玩家移动
inline def playerMove(CameraObject &_player) {
    if (SDL_GetTicks() - player_tick > 50) {
        player_tick = SDL_GetTicks();
        if (KeyDown('W'))
            _player.worldY -= 10;
        if (KeyDown('S'))
            _player.worldY += 10;
        if (KeyDown('A'))
            _player.worldX -= 10;
        if (KeyDown('D'))
            _player.worldX += 10;
    }
}

// 初始化
def init() {
    // 初始化SDL的一切(可以说是始祖级的代码了)
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        SDL_GetError();

    // 字体加载
    TTF_Init();
    STTS_LoadFont("font.ttf", 12);

    // 图片(暂时还用不上)
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    // 窗口
    window = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    // 渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    // 初始化按钮
    Button(WIN_WIDTH / 2, WIN_HEIGHT / 2, 50, 50); // 启动按钮
    for (auto &button : button_list)
        button.SetRenderer(renderer);

    // 输出窗口的ID(开发用途)
    // cout << SDL_GetWindowID(window);

    // 初始化计时器
    srand((unsigned int)time(NULL));
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
        if (!button_list.empty()) {
            for (auto &button : button_list) {
                if (button.handleEvent(&event)) {
                    button.clearButton(button);
                    return true;
                }
            }
        }
    }
    return false;
}

// 未进入游戏前的处理
def toStart() {
    while (1) {
        SDL_RenderClear(renderer);

        // 绘制按钮
        for (auto &button : button_list)
            button.render(true);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);

        if (handleEvent())
            break;
    }
}

// 设置标题
inline def setTitle(string title) {
    // 判断是否进入游戏，分为两种情况
    if (!IN_GAME) {
        // 点击运行时的情况(并没有点击到开始的按钮)
        SDL_SetWindowTitle(window, "版本: 内测版");
    } else {
        // 进入游戏后的情况
        string _title = title + " Player Position: X" +
                        to_string(player.worldX) + "Y" +
                        to_string(player.worldY);
        SDL_SetWindowTitle(window, _title.c_str());
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
        playerMove(player);
        Camera_LookAt(&camera, &player);
        def pos = Camera_WorldToScreen(&camera, &player, 0, 0);

        // 碰撞检测
        if (!ammo_list.empty())
            for (auto &ammo : ammo_list)
                if (checkCollisionAmmo(ammo))
                    ammo.alive = false;

        // 画出子弹
        updateAmmo(pos.x, pos.y );
        drawAmmo();

        // 绘制敌人
        def px = (long)player.worldX, py = (long)player.worldY;
        SIZE test = {(LONG)pos.x, (LONG)pos.y},
             test2 = {rand() % 1000, rand() % 1000};
        updateEnemy(test);
        createEnemy(100, 0, 3, test2, 10, 5);
        drawEnemy(camera.x, camera.y);

        // 画出炮台
        int circle_r = 10;
        SDL_DrawCircle(renderer, pos.x, pos.y, circle_r, {0, 0, 0, 255});

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        double angle = atan2(y - pos.y, x - pos.x);
        int endX = pos.x + 20 * cos(angle), endY = pos.y + 20 * sin(angle);
        thickLineRGBA(renderer, pos.x, pos.y, endX, endY, 3, 0,
                      0, 0, 255);

        // 显示杀敌数
        string text = "被你压力的敌人一共有" + to_string(kill_enemyNum) + "个";
        STTS_LoadFont("zh_font.ttf", 12);
        STTS_DrawCHN(renderer, text.c_str(), 0, 0, BLACK);

        // 测试区
        // system("cls");
        // for (auto i : ammo_list)
        //     cout << i.worldX << " " << i.worldY << '\n';

        SDL_UpdateWindowSurface(window);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);

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