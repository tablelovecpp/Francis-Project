#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

/* ------------- 公共接口 ------------- */

typedef struct {
    Uint8 r, g, b, a;
} STTS_Color;
/* 几个常用颜色常量 */
static const STTS_Color WHITE = {255, 255, 255, 255};
static const STTS_Color BLACK = {0, 0, 0, 255};
static const STTS_Color RED = {255, 0, 0, 255};

/* 释放内部缓存的字体 */
void STTS_Quit(void);

/* ------------- 内部实现 ------------- */

static TTF_Font *g_font = NULL;

inline int STTS_LoadFont(const char *ttfFile, int size) {
    STTS_Quit(); /* 如果之前加载过，先释放 */
    g_font = TTF_OpenFont(ttfFile, size);
    return g_font ? 0 : -1;
}

void STTS_DrawENG(SDL_Renderer *ren, const char *text, int x, int y,
                  STTS_Color c) {
    if (!g_font || !text || !ren)
        return;

    SDL_Surface *surf =
        TTF_RenderUTF8_Blended(g_font, text, (SDL_Color){c.r, c.g, c.b, c.a});
    if (!surf)
        return;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = {x, y, surf->w, surf->h};
    SDL_RenderCopy(ren, tex, NULL, &dst);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

void STTS_DrawCHN(SDL_Renderer *ren, const char *utf8text, int x, int y,
                  STTS_Color c) {
    if (!g_font || !utf8text || !ren)
        return;

    /* 使用 UTF-8 版本的渲染函数，支持中文 */
    SDL_Surface *surf = TTF_RenderUTF8_Blended(g_font, utf8text,
                                               (SDL_Color){c.r, c.g, c.b, c.a});
    if (!surf)
        return;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = {x, y, surf->w, surf->h};
    SDL_RenderCopy(ren, tex, NULL, &dst);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

inline void STTS_Quit(void) {
    if (g_font) {
        TTF_CloseFont(g_font);
        g_font = NULL;
    }
}