/* 炮弹 */

#pragma once
#include "stdc++.h"

USE namespace AMMO {
#define def static auto

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

#define CHECK if (!ammo_list.empty())

    // 子弹的列表
    static vector<Ammo> ammo_list;

    // 记录开始时间
    def start_time = SDL_GetTicks(), shoot_time = Uint32(0);

    // 子弹数量上限           射击间隔时间
    def ammo_max = 10, shoot_delaytTime = 200;
    // 是否正在射击
    def is_shooting = false;

    // 射出子弹
    def shootAmmo() {
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
    def updateAmmo() {
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
    def drawAmmo() {
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