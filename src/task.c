#include "../inc/task.h"
#include "../inc/engine.h"
#include "../inc/engine.h"

static t_task task_create(void) {
    t_task task = {0};
    task.health = TASK_RANDOM_HP;
    task.object = object_new();
    task.object->width = 48;
    task.object->height = 48;
    task.object->speed = TASK_SPEED;
    task.object->type = GAMEOBJECT_TASK;
    task.object->texture = NULL;
    return task;
}

int *tasks_get_next_index(void) {
    static int index = 0;
    for (int i = index; (i + 1) % MAX_TASKS != index;) {
        if (!objects_get()[i].is_active) {
            index = i;
            return &index;
        }
        i = (i + 1) % MAX_TASKS;
    }
    index = (index + 1) % MAX_TASKS;
    return &index;
}

bool *reset_tasks(void) {
    static bool reset = true;
    return &reset;
}

t_task *tasks_get(void) {
    static t_task task[MAX_TASKS] = {0};
    for (int i = 0; *reset_tasks() && i < MAX_TASKS; i++) {
        task[i] = task_create();
        *tasks_get_next_index() = 0;
    }
    *reset_tasks() = false;

    return task;
}

t_task *task_new(void) {
    return &tasks_get()[*tasks_get_next_index()];
}

void tasks_update(void) {
    t_task *tasks = tasks_get();

    for (int i = 0; i < MAX_TASKS; i++) {
        t_gameobject *obj = tasks[i].object;
        if (!obj || !obj->is_active)
            continue;

        Uint32 time_alive = SDL_GetTicks() - obj->spawn_time;

        if (time_alive < 4000) {
            obj->speed = TASK_SPEED * (rand() % 3 + 2);
        }

        else {
            obj->speed -= 0.1;
            if (obj->speed < TASK_SPEED)
                obj->speed = TASK_SPEED;
        }

        obj->x += cos(obj->angle * M_PI / 180.0) * obj->speed;
        obj->y += sin(obj->angle * M_PI / 180.0) * obj->speed;
    }
}
