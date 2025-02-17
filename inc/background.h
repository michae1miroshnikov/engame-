#pragma once

#include "../inc/gamelib.h"
#include "../inc/engine.h"
#include "../inc/gameobject.h"
#include "../inc/movement.h"
#include "../inc/game.h"
#include <stdbool.h>

#define MAX_STARS 100
#define STAR_SPEED rand() % 3 / 10.0 + 0.05
#define STAR_ROTATION_SPEED 0
#define STAR_ACCELERATION 0
#define STAR_MAX_SPEED 2.0
#define STAR_DECELERATION 0.01
#define STAR_BOOST_FACTOR 3.0
void init_stars(void);
void init_stars(void);
