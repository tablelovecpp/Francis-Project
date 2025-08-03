/* 炮弹 */

#pragma once
#include "stdc++.h"

USE namespace AMMO {
#define DEF static auto

    struct Ammo {
        // 变量
        SIZE pos;
        int speed, damage;
        bool alive;
        float angle;

        // 函数
        Ammo() {}
        Ammo(int x, int y, int speed, int attack, float angle)
            : pos({x, y}), speed(speed), damage(attack), alive(true) {
            this->angle = angle;
        }

        // 更新子弹
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

#define CHECK if (!ammo_list.empty())

    // 子弹的列表
    DEF ammo_list = vector<Ammo>();

    // 记录开始时间
    DEF start_time = SDL_GetTicks(), shoot_time = Uint32(0);

    // 子弹数量上限           射击间隔时间
    DEF ammo_max = 10, shoot_delaytTime = 200;
    // 是否正在射击
    DEF is_shooting = false;

    // 射出子弹
    DEF shootAmmo() {
        if (KeyDown(VK_LBUTTON)) {
            // 获取窗口大小和鼠标位置
            auto width = 0, height = 0;
            SDL_GetWindowSize(SDL_GetWindowFromID(1), &width, &height);

            auto x = 0, y = 0;
            SDL_GetMouseState(&x, &y);

            auto angle = atan2(y - height / 2, x - width / 2);
            auto player_ammo = Ammo(width / 2, height / 2, 10, 10, angle);

            ammo_list.push_back(player_ammo);
            is_shooting = true, shoot_time = SDL_GetTicks();
        }
    }

    // 更新子弹
    DEF updateAmmo() {
        // 判断是否触碰敌人，如果是消除子弹和敌人


        if ((SDL_GetTicks() - shoot_time) >= shoot_delaytTime && shoot_time) {
            is_shooting = false;
            shoot_time = 0;
        }
        if (!is_shooting)
            shootAmmo();
        if ((SDL_GetTicks() - start_time) % 10 == 0 &&
            SDL_GetTicks() > start_time) {
            start_time = SDL_GetTicks();
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
    }

    // 绘制子弹
    DEF drawAmmo() {
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