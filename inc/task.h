#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include "gameobject.h"

#define TASK_MAX_HP 3
#define MAX_TASKS 55
#define TASK_SPEED 2
#define TASK_RANDOM_HP rand() % TASK_MAX_HP + 1

typedef struct s_task {
    unsigned short health;
    t_gameobject *object;
}              t_task;

t_task *task_new(void);
bool *reset_tasks(void);
t_task *tasks_get(void);
void task_on_hit(t_task *task);
int *tasks_get_next_index(void);
void tasks_update(void);
