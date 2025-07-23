#pragma once
#include "stdc++.h"
#ifdef USE_MY_LIB
#define USE inline
#else
#define USE
#endif

// 玩家
USE namespace PLAYER {
    struct Player {
        SIZE pos;
        int health, id;
        bool is_alive;
        string name;

        Player() {}
        Player(SIZE pos, int player_id, int health, string name)
            : pos(pos), id(player_id), health(health), name(name),
              is_alive(true) {}
    };
    typedef vector<Player> Players;

    static auto Render_Player(SDL_Renderer* renderer, Player p) {
        SDL_Color _color = {255, 255, 255, 255};
        SDL_DrawCircle(renderer, p.pos.cx, p.pos.cy, 10, _color);
    }
}