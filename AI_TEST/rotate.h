#ifndef ROTATION_UTILS_H
#define ROTATION_UTILS_H

#include "../SDL2/SDL.h"
#include <cmath>

/**
 * 旋转功能工具类
 */
class RotationUtils {
  private:
    static float currentAngle; // 当前旋转角度（弧度）

  public:
    /**
     * 更新旋转角度
     * @param speed 旋转速度（度/帧）
     */
    static void updateRotation(float speed);

    /**
     * 计算围绕中心点旋转后的坐标
     * @param centerX 中心点X坐标
     * @param centerY 中心点Y坐标
     * @param radius 旋转半径
     * @param angle 旋转角度（弧度），如果为-1则使用当前角度
     * @return 旋转后的坐标点
     */
    static SDL_Point getRotatedPosition(float centerX, float centerY,
                                        float radius, float angle = -1.0f);

    /**
     * 重置旋转角度
     */
    static void resetAngle();

    /**
     * 获取当前旋转角度
     * @return 当前角度（弧度）
     */
    static float getCurrentAngle();

    /**
     * 设置当前旋转角度
     * @param angle 新的角度（弧度）
     */
    static void setCurrentAngle(float angle);

    /**
     * 角度转弧度
     * @param degrees 角度
     * @return 弧度值
     */
    static float degreesToRadians(float degrees);

    /**
     * 弧度转角度
     * @param radians 弧度
     * @return 角度值
     */
    static float radiansToDegrees(float radians);
};

// 静态成员初始化
float RotationUtils::currentAngle = 0.0f;

// 实现
inline void RotationUtils::updateRotation(float speed) {
    currentAngle += degreesToRadians(speed);
    if (currentAngle >= 2.0f * M_PI) {
        currentAngle -= 2.0f * M_PI;
    }
}

inline SDL_Point RotationUtils::getRotatedPosition(float centerX, float centerY,
                                                   float radius, float angle) {
    float useAngle = (angle < 0) ? currentAngle : angle;

    SDL_Point point;
    point.x = static_cast<int>(centerX + radius * cos(useAngle));
    point.y = static_cast<int>(centerY + radius * sin(useAngle));
    return point;
}

inline void RotationUtils::resetAngle() { currentAngle = 0.0f; }

inline float RotationUtils::getCurrentAngle() { return currentAngle; }

inline void RotationUtils::setCurrentAngle(float angle) {
    currentAngle = angle;
}

inline float RotationUtils::degreesToRadians(float degrees) {
    return degrees * M_PI / 180.0f;
}

inline float RotationUtils::radiansToDegrees(float radians) {
    return radians * 180.0f / M_PI;
}

#endif // ROTATION_UTILS_H
