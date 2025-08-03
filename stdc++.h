// AllHeaders.h
#pragma once

// 输入输出
#include <fstream>
#include <iostream>
#include <sstream>

// 容器
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// 算法
#include <algorithm>
#include <iterator>
#include <numeric>

// 字符串
#include <cstring>
#include <string>

// 多线程
#include <future>
#include <mutex>
#include <thread>

// 时间和日期
#include <chrono>
#include <ctime>

// 内存管理
#include <memory>
#include <new>

// 异常处理
#include <exception>
#include <stdexcept>

// 类型支持
#include <type_traits>
#include <typeinfo>

// 其他
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <ios>
#include <limits>
#include <locale>
#include <ratio>
#include <system_error>
#include <tuple>
#include <utility>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "SDL2/SDL2_framerate.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL2_gfxPrimitives_font.h"
#include "SDL2/SDL2_imageFilter.h"
#include "SDL2/SDL2_rotozoom.h"

#include <conio.h>
#include <windows.h>

// 使用所有标准库
using namespace std;

// 适配short变量的SIZE结构体
struct SSIZE {
    short cx, cy;
};

// 获取窗口大小
static SIZE get_window_size() {
    DEVMODE dm;
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
    int x = dm.dmPelsWidth;
    int y = dm.dmPelsHeight;
    return {x, y};
}

// 绘制圆
static auto SDL_DrawCircle(SDL_Renderer *renderer, int x0, int y0, int radius,
                           SDL_Color color) {
    const int n = 200; // number of triangles used to draw the circle
    SDL_Vertex vertices[n + 1];
    for (int i = 0; i <= n; i++) {
        float angle = 2 * M_PI * i / n;
        vertices[i].position.x = x0 + radius * cos(angle);
        vertices[i].position.y = y0 + radius * sin(angle);
        vertices[i].color = color;
    }
    int indices[3 * n];
    for (int i = 0; i < n; i++) {
        indices[3 * i] = 0;
        indices[3 * i + 1] = i + 1;
        indices[3 * i + 2] = (i + 1) % n + 1;
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderGeometry(renderer, NULL, vertices, n + 1, indices, 3 * n);
}

// 获取按键
inline auto KeyDown(short key) {
    if (key >= 'a' && key <= 'z')
        key -= 'a' - 'A'; // 转换为大写
    return GetAsyncKeyState(key) & 0x8000;
}

/**
 * 检测两个矩形是否发生碰撞
 *
 * @param rectA 第一个矩形
 * @param rectB 第二个矩形
 * @return 如果矩形碰撞返回1（true），否则返回0（false）
 */
static auto checkCollision(SDL_Rect rectA, SDL_Rect rectB) {
    // 矩形A的右边界
    int rightA = rectA.x + rectA.w;
    // 矩形A的下边界
    int bottomA = rectA.y + rectA.h;

    // 矩形B的右边界
    int rightB = rectB.x + rectB.w;
    // 矩形B的下边界
    int bottomB = rectB.y + rectB.h;

    // 检测碰撞条件
    // 如果任一条件为真，则没有发生碰撞
    if (rectA.x >= rightB || rectB.x >= rightA || rectA.y >= bottomB ||
        rectB.y >= bottomA) {
        return 0; // 没有碰撞
    }

    return 1; // 发生碰撞
}

// 引用库的操作
#ifdef USE_MY_LIB
#define USE inline
#else
#define USE
#endif