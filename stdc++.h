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
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

#include "SDL2/SDL2_imageFilter.h"
#include "SDL2/SDL2_rotozoom.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL2_gfxPrimitives_font.h"
#include "SDL2/SDL2_framerate.h"


#include <windows.h>
#include <conio.h>

// All Namespaces
using namespace std;

struct SSIZE {
    short cx, cy;
};
static SIZE get_window_size() {
    DEVMODE dm;
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm);
    int x = dm.dmPelsWidth;
    int y = dm.dmPelsHeight;
    return {x, y};
}

static void SDL_DrawCircle(SDL_Renderer *renderer, int x0, int y0, int radius,
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
    SDL_RenderGeometry(renderer, NULL, vertices, n + 1, indices, 3 * n);
}