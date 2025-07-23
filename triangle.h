#pragma once
#include "stdc++.h"
#define def auto
#ifdef USE_MY_LIB
#define INLINE inline
#else
#define INLINE
#endif

INLINE namespace SDL_LIB_NAMESPACE {
    struct SDL_Triangle {
        // 变量
        SDL_Vertex points[3];

        // 函数
        SDL_Triangle() {}
        SDL_Triangle(SDL_Vertex p1, SDL_Vertex p2, SDL_Vertex p3)
            : points{p1, p2, p3} {}
    };

    static def Render_Triangle(SDL_Renderer * renderer, SDL_Triangle triangle) {
        def _size = sizeof(triangle.points) / sizeof(triangle.points[0]);

        SDL_RenderGeometry(renderer, nullptr, triangle.points, _size, nullptr,
                           0);
    }
} // namespace SDL_LIB_NAMESPACE