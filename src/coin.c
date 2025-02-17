#include "../inc/game_over.h"
#include "../inc/coin.h"
#include "../inc/game.h"
#include "../inc/engine.h"
#include <stdlib.h>

// static SDL_Texture *load_coin_texture(SDL_Renderer *renderer) {
//     return loadTexture(renderer, "./resource/coin.png");
// }

static t_coin coin_create(void) {
    t_coin coin = {0};
    coin.object = object_new();
    if (coin.object) {
        coin.object->type = GAMEOBJECT_COIN;
        coin.object->width = 30;
        coin.object->height = 30;
        coin.object->speed = 2;
        coin.object->is_active = false;
        coin.object->angle = 0;
        coin.object->texture =
            loadTexture(game_get()->renderer, "./resource/sprites/coin.png");
        if (!coin.object->texture) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ERROR, "Failed to find coin texture");
            exit(1);
        }
    }
    return coin;
}

bool *reset_coins(void) {
    static bool reset = true;
    return &reset;
}

t_coin *coins_get(void) {
    static t_coin coin[MAX_COINS] = {0};
    for (int i = 0; *reset_coins() && i < MAX_COINS; i++) {
        coin[i] = coin_create();
    }
    *reset_coins() = false;

    return coin;
}

size_t get_next_coin(void) {
    t_coin *coins = coins_get();
    if (!coins)
        return 0;

    for (int i = 0; i < MAX_COINS; i++) {
        if (coins[i].object && !coins[i].object->is_active) {
            return i;
        }
    }
    return rand() % MAX_COINS;
}

void update_coins(void) {
    t_coin *coins = coins_get();

    for (size_t i = 0; i < MAX_COINS; i++) {
        if (!coins[i].object)
            continue;

        if (coins[i].object->is_active) {
            coins[i].life_time++;
            if (coins[i].life_time >= 1000) {
                coins[i].object->is_active = false;
            }
        }
    }
}

void generate_coin(t_gameobject *obj) {
    size_t next_index = get_next_coin();
    t_coin *coin = &coins_get()[next_index];

    if (!coin->object)
        return;

    coin->life_time = 0;
    coin->object->angle = obj->angle;
    coin->object->x = obj->x;
    coin->object->y = obj->y;
    coin->object->is_active = true;
}
