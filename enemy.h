/* 敌人 */

#pragma once
#define USE_MY_LIB

#include "ammo.h"
#include "stdc++.h"

USE namespace ENEMY {
#define DEF static auto

    // 敌人结构体
    struct Enemy {
        int health, damage, move_speed, size;
        SIZE pos;

        Enemy() {}
        Enemy(int health, int damage, int move_speed, SIZE pos, int size)
            : health(health), damage(damage), move_speed(move_speed), pos(pos),
              size(size) {}

        auto operator==(const Enemy &other) {
            return health == other.health && damage == other.damage &&
                   move_speed == other.move_speed && size == other.size &&
                   pos.cx == other.pos.cx && pos.cy == other.pos.cy;
        }
    };

    // 敌人的列表
    DEF enemy_list = vector<Enemy>();

    // 创建敌人的间隔的时间      更新敌人的间隔的时间
    DEF create_time = 0, update_time = 0;

    // 杀敌数
    DEF kill_enemyNum = 0;

    // 和子弹的碰撞检测
    DEF checkCollisionAmmo(Ammo ammo) {
        SDL_Rect ammo_rect = {ammo.pos.cx - ammo.size, ammo.pos.cy - ammo.size,
                              ammo.size * 2, ammo.size * 2};
        if (!enemy_list.empty()) {
            for (auto &enemy : enemy_list) {
                SDL_Rect enemy_rect = {enemy.pos.cx - enemy.size,
                                       enemy.pos.cy - enemy.size,
                                       enemy.size * 2, enemy.size * 2};
                SDL_RenderDrawRect(SDL_GetRenderer(SDL_GetWindowFromID(1)),
                                   &enemy_rect);
                if (checkCollision(ammo_rect, enemy_rect)) {
                    enemy.health -= ammo.damage;
                    return true;
                } else
                    return false;
            }
        }
        return false;
    }

    // 和玩家的碰撞检测
    DEF checkCollisionPlayer(SIZE player_pos) {}

    // 创建敌人
    DEF createEnemy(int health, int damage, int move_speed, SIZE pos, int size,
                    int enemy_num) {
        if (SDL_GetTicks() - create_time > 5000 &&
            enemy_list.size() < enemy_num) {
            enemy_list.push_back({health, damage, move_speed, pos, size});
            create_time = SDL_GetTicks();
        }
    }

    // 更新敌人
    DEF updateEnemy(SIZE _player_pos) {
        for (auto &enemy : enemy_list) {
            // 检测敌人是否死亡，如果死亡就移除敌人
            if (enemy.health <= 0) {
                enemy_list.erase(
                    remove(enemy_list.begin(), enemy_list.end(), enemy),
                    enemy_list.end());
                kill_enemyNum++;
                continue;
            }
            if ((SDL_GetTicks() - update_time) > 1000) {
                
                /* 敌人自动移动到玩家位置 */
                auto espeed = (LONG)enemy.move_speed; // 移动速度

                // X坐标的移动
                auto ex = enemy.pos.cx, px = _player_pos.cx;
                if (abs(ex - px) < espeed)
                    ex = px;
                else if (ex > px && (ex - px) > espeed)
                    ex -= enemy.move_speed;
                else if (ex < px && (px - ex) > espeed)
                    ex += enemy.move_speed;

                // Y坐标的移动
                auto ey = enemy.pos.cy, py = _player_pos.cy;
                if (abs(ey - py) < espeed)
                    ey = py;
                else if (ey > py && (ey - py) > espeed)
                    ey -= enemy.move_speed;
                else if (ey < py && (py - ey) > espeed)
                    ey += enemy.move_speed;
                enemy.pos = {ex, ey};
                update_time = SDL_GetTicks();
            }
        }
    }

    // 绘制敌人
    DEF drawEnemy(int camX, int camY) {
        auto renderer = SDL_GetRenderer(SDL_GetWindowFromID(1));
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        if (!enemy_list.empty()) {
            for (auto enemy : enemy_list) {
                int cx = enemy.pos.cx, cy = enemy.pos.cy;
                SDL_DrawCircle(renderer, enemy.pos.cx, enemy.pos.cy, enemy.size,
                               {255, 0, 0, 255});
            }
        }
    }
}