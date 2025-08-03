/* 敌人 */

#pragma once
#include "stdc++.h"
#include "ammo.h"

USE namespace ENEMY {
#define DEF static auto

    // 敌人结构体
    struct Enemy {
        int health, damage, move_speed;
        SIZE pos;

        Enemy() {}
        Enemy(int health, int damage, int move_speed, SIZE pos)
            : health(health), damage(damage), move_speed(move_speed), pos(pos) {

        }
    };

    // 敌人的列表
    DEF enemy_list = vector<Enemy>();

    // 创建敌人的间隔的时间      更新敌人的间隔的时间
    DEF create_time = 0, update_time = 0;

    // 创建敌人
    DEF createEnemy(int health, int damage, int move_speed, SIZE pos,
                    int enemy_num) {
        if (SDL_GetTicks() - create_time > 1000 &&
            enemy_list.size() < enemy_num) {
            enemy_list.push_back({health, damage, move_speed, pos});
            create_time = SDL_GetTicks();
        }
    }

    // 更新敌人
    DEF updateEnemy(SIZE _player_pos) {
        if (!enemy_list.empty() && SDL_GetTicks() - update_time > 20) {
            for (auto &enemy : enemy_list) {
                // 检测敌人是否死亡，如果死亡就移除敌人
                if (enemy.health <= 0)
                    enemy_list.erase(enemy_list.begin() + enemy_list.size() -
                                     1);

                auto ex = enemy.pos.cx, ey = enemy.pos.cy,
                     espeed = (LONG)enemy.move_speed, px = _player_pos.cx,
                     py = _player_pos.cy;

                // X坐标的移动
                if (abs(ex - px) < espeed)
                    ex = px;
                else if (ex > px && (ex - px) > espeed)
                    ex -= enemy.move_speed;
                else if (ex < px && (px - ex) > espeed)
                    ex += enemy.move_speed;

                // Y坐标的移动
                if (abs(ey - py) < espeed)
                    ey = py;
                else if (ey > py && (ey - py) > espeed)
                    ey -= enemy.move_speed;
                else if (ey < py && (py - ey) > espeed)
                    ey += enemy.move_speed;
                enemy.pos = {ex, ey};
            }
            update_time = SDL_GetTicks();
        }
    }

    // 绘制敌人
    DEF drawEnemy() {
        auto renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if (!enemy_list.empty()) {
            for (auto enemy : enemy_list) {
                SDL_DrawCircle(renderer, enemy.pos.cx, enemy.pos.cy, 10,
                               {255, 0, 0, 255});
            }
        }
    }
}