#pragma once

#include "../inc/gameobject.h"
#include <math.h>


#define MAX_COINS 30
#define COIN_ROTATION_SPEED 3.0
#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)
#define MOVE_SPEED 1

typedef struct s_coin {
    int life_time;
    t_gameobject *object;
}              t_coin;


t_coin coin_new(void);
void generate_coin(t_gameobject *obj);
void update_coins(void);
size_t get_next_coin(void);
t_coin *coins_get(void);
bool *reset_coins(void);
