#ifndef SIMPLE_MOUSE_ROTATOR_H
#define SIMPLE_MOUSE_ROTATOR_H

#include "../SDL2/SDL.h"
#include <cmath>

/**
 * 简单的围绕鼠标旋转图形类
 */
class SimpleMouseRotator {
  private:
    SDL_Renderer *renderer;
    SDL_Point mousePos;    // 鼠标位置
    float angle;           // 当前旋转角度（弧度）
    float rotationSpeed;   // 旋转速度
    float radius;          // 旋转半径
    int objectSize;        // 图形大小
    SDL_Color objectColor; // 图形颜色

  public:
    /**
     * 构造函数
     * @param renderer SDL渲染器
     * @param speed 旋转速度（度/帧）
     * @param rotRadius 旋转半径
     * @param size 图形大小
     * @param color 图形颜色
     */
    SimpleMouseRotator(SDL_Renderer *renderer, float speed = 2.0f,
                       float rotRadius = 100.0f, int size = 10,
                       SDL_Color color = {255, 0, 0, 255});

    /**
     * 更新鼠标位置
     * @param x 鼠标x坐标
     * @param y 鼠标y坐标
     */
    void updateMousePosition(int x, int y);

    /**
     * 更新旋转状态
     */
    void update();

    /**
     * 渲染旋转图形
     */
    void render();

    /**
     * 设置旋转速度
     * @param speed 新的旋转速度（度/帧）
     */
    void setRotationSpeed(float speed);

    /**
     * 设置旋转半径
     * @param newRadius 新的旋转半径
     */
    void setRadius(float newRadius);

    /**
     * 设置图形颜色
     * @param color 新的颜色
     */
    void setColor(SDL_Color color);

  private:
    /**
     * 角度转弧度
     * @param degrees 角度
     * @return 弧度值
     */
    float degreesToRadians(float degrees);

    /**
     * 绘制填充圆形
     * @param centerX 中心x坐标
     * @param centerY 中心y坐标
     * @param radius 半径
     */
    void drawFilledCircle(int centerX, int centerY, int radius);
};

// 实现
inline SimpleMouseRotator::SimpleMouseRotator(SDL_Renderer *renderer,
                                              float speed, float rotRadius,
                                              int size, SDL_Color color)
    : renderer(renderer), angle(0.0f), rotationSpeed(speed), radius(rotRadius),
      objectSize(size), objectColor(color) {
    mousePos = {0, 0};
}

inline void SimpleMouseRotator::updateMousePosition(int x, int y) {
    mousePos.x = x;
    mousePos.y = y;
}

inline void SimpleMouseRotator::update() {
    angle += degreesToRadians(rotationSpeed);
    if (angle >= 2.0f * M_PI) {
        angle -= 2.0f * M_PI;
    }
}

inline void SimpleMouseRotator::render() {
    // 计算旋转图形的位置
    int objectX = mousePos.x + static_cast<int>(radius * cos(angle));
    int objectY = mousePos.y + static_cast<int>(radius * sin(angle));

    // 设置颜色并绘制旋转图形
    SDL_SetRenderDrawColor(renderer, objectColor.r, objectColor.g,
                           objectColor.b, objectColor.a);
    drawFilledCircle(objectX, objectY, objectSize);

    // 绘制鼠标中心点（可选）
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    drawFilledCircle(mousePos.x, mousePos.y, 2);
}

inline void SimpleMouseRotator::setRotationSpeed(float speed) {
    rotationSpeed = speed;
}

inline void SimpleMouseRotator::setRadius(float newRadius) {
    radius = newRadius;
}

inline void SimpleMouseRotator::setColor(SDL_Color color) {
    objectColor = color;
}

inline float SimpleMouseRotator::degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0f;
}

inline void SimpleMouseRotator::drawFilledCircle(int centerX, int centerY,
                                                 int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

#endif // SIMPLE_MOUSE_ROTATOR_H
