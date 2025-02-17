#pragma once

#include "gamelib.h"
#include "engine.h"
#include "gameobject.h"
#include "movement.h"
#include <stdbool.h>

#define ROTATION_SPEED 5.0
#define MOVEMENT_ACCELERATION 0.35
#define MAX_MOVEMENT_SPEED 8.0
#define MOVEMENT_DECELERATION 0.95
#define ROTATION_ANGLE 5
#define BOOST_FACTOR 2.0

typedef struct s_bee {
    t_missile missiles[MAX_MISSILES];
    t_gameobject *object;
    t_movement_state movement;
    SDL_Texture *flame_texture;
    bool can_shoot;
    bool is_boosting;
    short coins;
    int next_missile;
    double stamina;
}              t_bee;

t_bee *get_bee(void);
bool *reset_bee(void);
