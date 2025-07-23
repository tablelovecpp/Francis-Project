/* 炮弹 */

#pragma once
#include "stdc++.h"

USE namespace AMMO {
    struct Ammo {
        // 变量
        SIZE pos;
        int speed, attack;
        bool alive;
        float angle;

        // 函数
        Ammo() {}
        Ammo(int x, int y, int speed, int attack, float angle)
            : pos({x, y}), speed(speed), attack(attack), alive(true) {
            this->angle = angle;
        }

        auto update() {
            auto width = 0, height = 0;
            SDL_GetWindowSize(SDL_GetWindowFromID(1), &width, &height);
            if (pos.cx < 0 || pos.cx >= width || pos.cy < 0 || pos.cy >= height)
                alive = false;
            else
                pos.cx += speed * cos(angle), pos.cy += speed * sin(angle);
        }

        auto operator==(const Ammo &other) {
            return pos.cx == other.pos.cx && pos.cy == other.pos.cy;
        }
    };

    // 子弹的列表
    static vector<Ammo> ammo_list;
    static SDL_TimerID ammo_timer;
#define CHECK if (!ammo_list.empty())

    // 射出子弹
    static auto shootAmmo() {
        if (KeyDown(VK_LBUTTON)) {
            // 获取窗口大小和鼠标位置
            auto width = 0, height = 0;
            SDL_GetWindowSize(SDL_GetWindowFromID(1), &width, &height);

            auto x = 0, y = 0;
            SDL_GetMouseState(&x, &y);

            auto angle = atan2(y - height / 2, x - width / 2);
            auto player_ammo = Ammo(width / 2, height / 2, 10, 10, angle);

            ammo_list.push_back(player_ammo);
        }
    }

    // 更新子弹
    static auto updateAmmo() {
        shootAmmo();
        CHECK
        for (auto &ammo : ammo_list) {
            if (ammo.alive)
                ammo.update();
            else
                ammo_list.erase(
                    remove(ammo_list.begin(), ammo_list.end(), ammo),
                    ammo_list.end());
        }
    }

    // 绘制子弹
    static auto drawAmmo() {
        auto renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));

        CHECK
        for (auto &ammo : ammo_list) {
            if (ammo.alive) {
                auto ammo_x = ammo.pos.cx, ammo_y = ammo.pos.cy;
                SDL_DrawCircle(renderer, ammo_x, ammo_y, 5, {0, 255, 255, 255});
            }
        }
    }
} // namespace AMMO