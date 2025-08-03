#ifndef CAMERA_H
#define CAMERA_H

#include "stdc++.h"

USE namespace CAMERA {
    typedef struct {
        float worldX; // 物体在世界中的真实坐标
        float worldY;
    } CameraObject;

    typedef struct {
        int screenW;
        int screenH;
        float x; // 视口左上角在世界中的坐标
        float y;
    } Camera;

    /* 创建相机 */
    static inline Camera Camera_Create(int screenW, int screenH) {
        return (Camera){.screenW = screenW, .screenH = screenH, .x = 0, .y = 0};
    }

    /* 让某个对象始终处于屏幕中心 */
    static inline void Camera_LookAt(Camera * cam, const CameraObject *obj) {
        cam->x = obj->worldX - cam->screenW * 0.5f;
        cam->y = obj->worldY - cam->screenH * 0.5f;
    }

    /* 世界坐标 -> 屏幕坐标 */
    static inline SDL_FRect Camera_WorldToScreen(
        const Camera *cam, const CameraObject *obj, int w, int h) {
        return (SDL_FRect){.x = obj->worldX - cam->x,
                           .y = obj->worldY - cam->y,
                           .w = (float)w,
                           .h = (float)h};
    }

    /* 直接给 SDL_Rect 的版本（整数） */
    static inline SDL_Rect Camera_WorldToScreenRect(
        const Camera *cam, const CameraObject *obj, int w, int h) {
        SDL_FRect f = Camera_WorldToScreen(cam, obj, w, h);
        return (SDL_Rect){(int)f.x, (int)f.y, w, h};
    }
}

#endif /* CAMERA_H */