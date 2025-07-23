#pragma once
#include "stdc++.h"

namespace {
class Button {
  public:
    Button(int x, int y, int w, int h);
    ~Button() = default;
    void render(bool isFill);
    bool handleEvent(SDL_Event *e);
    void SetRenderer(SDL_Renderer *renderer);
    SSIZE getButtonPosition() const;
    SSIZE getButtonSize() const;
    void clearButton() const;

  private:
    SDL_Renderer *mRenderer;
    SDL_Rect mRect;
    bool mMouseOver;
    int colors[4] = {0x00, 0x00, 0x00, 0x00};
};

Button::Button(int x, int y, int w, int h) : mMouseOver(false) {
    this->mRect = {x - w / 2, y - h / 2, w, h};
}

void Button::SetRenderer(SDL_Renderer *renderer) { this->mRenderer = renderer; }

void Button::render(bool isFill) {
    SDL_SetRenderDrawColor(mRenderer, colors[0], colors[1], colors[2],
                           colors[3]);

    // 绘制矩形
    if (isFill)
        SDL_RenderFillRect(mRenderer, &mRect);
    else
        SDL_RenderDrawRect(mRenderer, &mRect);
}

bool Button::handleEvent(SDL_Event *e) {
    if (mMouseOver)
        colors[0] = 0x00, colors[1] = 0xFF, colors[2] = 0x00,
        colors[3] = 0xFF; // 绿色
    else
        colors[0] = 0xFF, colors[1] = 0x00, colors[2] = 0x00,
        colors[3] = 0xFF; // 红色

    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        // 检查鼠标是否在按钮内
        if (x < mRect.x || x > mRect.x + mRect.w || y < mRect.y ||
            y > mRect.y + mRect.h)
            inside = false;

        if (!inside)
            mMouseOver = false;
        else {
            mMouseOver = true;
            if (e->type == SDL_MOUSEBUTTONDOWN) {
                std::cout << "Button pressed!" << std::endl;
                colors[0] = 0x00, colors[1] = 0x00, colors[2] = 0xFF,
                colors[3] = 0xFF; // 蓝色
                return true;
            }
        }
    }
    return false;
}

SSIZE Button::getButtonPosition() const {
    auto x = static_cast<short>(mRect.x + mRect.w / 2);
    auto y = static_cast<short>(mRect.y + mRect.h / 2);
    return {x, y};
}

SSIZE Button::getButtonSize() const {
    auto w = static_cast<short>(mRect.w);
    auto h = static_cast<short>(mRect.h);
    return {w, h};
}

// 清除按钮并释放内存
void Button::clearButton() const {
    delete this;
}
} // namespace