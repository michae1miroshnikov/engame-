#pragma once

#include "gameobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "sprint.h"
#include "coin.h"

#define MAX_MISSILES 10
#define MISSILE_SPEED 20
#define MISSILE_SIZE 3


typedef struct s_missile {
    t_gameobject *object;
    Uint32 lifetime;
    Uint32 spawn_time; 
}              t_missile;

int get_next_missile(t_missile *missiles);
void shoot(t_missile *missile);
void updateMissiles(void);

