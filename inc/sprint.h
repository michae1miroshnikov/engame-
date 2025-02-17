#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "gameobject.h"
#include "task.h"

#define SPRINT_SPEED 2
#define MAX_SPRINTS 5
#define SPRINT_MEDIUM_MIN_TASKS 4
#define SPRINT_MEDIUM_MAX_TASKS 6
#define SPRINT_BIG_MIN_TASKS 7
#define SPRINT_BIG_MAX_TASKS 11
#define SPRINT_MOVE_DELAY_MS 0

typedef struct s_task t_task;
typedef struct s_gameobject t_gameobject;
typedef struct s_coin t_coin;


typedef enum e_sprint_size {
    SPRINT_SIZE_MEDIUM,
    SPRINT_SIZE_BIG
}           t_sprint_size;

typedef struct s_sprint {
    int health;
    int task_length;
    t_sprint_size size;
    t_task *tasks;
    t_gameobject *object;
}              t_sprint;

t_sprint *sprint_new(void);
t_sprint *sprints_get(void);
void sprint_on_hit(t_sprint *sprint);
void sprints_spawn(void);
bool *reset_sprints(void);
bool endgame(void);
