#include "../inc/sprint.h"
#include "../inc/gamelib.h"
#include "../inc/engine.h"
#include "../inc/task.h"
#include "../inc/game.h"

static t_sprint sprint_create(void) {
    t_sprint sprint = {0};
    int grid_size = sqrt(MAX_SPRINTS);
    int grid_x = (rand() % MAX_SPRINTS) % grid_size;
    int grid_y = (rand() % MAX_SPRINTS) / grid_size;
    int cell_width = WINDOW_WIDTH / grid_size;
    int cell_height = WINDOW_HEIGHT / grid_size;
    sprint.size = (rand() % 2 == 0) ? SPRINT_SIZE_MEDIUM : SPRINT_SIZE_BIG;
    sprint.health = (sprint.size == SPRINT_SIZE_MEDIUM) ? 1 : (2 + rand() % 2);
    sprint.tasks = &tasks_get()[*tasks_get_next_index()];
    sprint.task_length =
        (sprint.size == SPRINT_SIZE_MEDIUM)
            ? SPRINT_MEDIUM_MIN_TASKS + (rand() % (SPRINT_MEDIUM_MAX_TASKS -
                                                   SPRINT_MEDIUM_MIN_TASKS + 1))
            : SPRINT_BIG_MIN_TASKS +
                  (rand() % (SPRINT_BIG_MAX_TASKS - SPRINT_BIG_MIN_TASKS + 1));
    for (int i = 0; i < sprint.task_length; i++) {
        task_new();
        char path[32];
        sprintf(path, "./resource/sprites/task_%02d.png", i);
        sprint.tasks[i].object->texture =
            loadTexture(game_get()->renderer, path);
        if (!sprint.tasks[i].object->texture) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ERROR,
                        "Failed to find task texture %s",
                        path);
            exit(1);
        }
    }
    sprint.object = object_new();
    sprint.object->x = (grid_x * cell_width) + (rand() % cell_width);
    sprint.object->y = (grid_y * cell_height) + (rand() % cell_height);
    sprint.object->type = GAMEOBJECT_SPRINT;
    sprint.object->angle = rand() % 360;
    sprint.object->speed = SPRINT_SPEED;
    sprint.object->width = (sprint.size == SPRINT_SIZE_BIG) ? 48 : 32;
    sprint.object->height = sprint.object->width;
    return sprint;
}

bool *reset_sprints(void) {
    static bool reset = true;
    return &reset;
}

t_sprint *sprints_get(void) {
    static t_sprint sprint[MAX_SPRINTS] = {0};
    for (int i = 0; *reset_sprints() && i < MAX_SPRINTS; i++) {
        char path[34];
        sprintf(path, "./resource/sprites/sprint_%02d.png", i);
        sprint[i] = sprint_create();
        sprint[i].object->texture = loadTexture(game_get()->renderer, path);
        if (!sprint[i].object->texture) {
            SDL_LogWarn(SDL_LOG_CATEGORY_ERROR,
                        "Failed to find task texture %s",
                        path);
            exit(1);
        }
    }
    *reset_sprints() = false;

    return sprint;
}

void sprints_spawn(void) {
    for (int i = 0; i < MAX_SPRINTS; i++) {
        sprints_get()[i].object->is_active = true;
    }
}

static void spawn_sprint_tasks(t_sprint *sprint) {
    double spread_radius = sprint->size == SPRINT_SIZE_MEDIUM ? 48.0 : 64.0;

    for (int i = 0; i < sprint->task_length; i++) {
        t_task *task = &sprint->tasks[i];
        double angle = (2 * M_PI * i) / sprint->task_length;
        int sprint_size = (sprint->size == SPRINT_SIZE_BIG) ? 48 : 32;
        task->object->x =
            sprint->object->x + (sprint_size / 2) + cos(angle) * spread_radius;
        task->object->y =
            sprint->object->y + (sprint_size / 2) + sin(angle) * spread_radius;
        task->object->is_active = true;
        task->object->angle = rand() % 360;

        task->object->speed = TASK_SPEED * (rand() % 3 + 2);
    }
}

void sprint_on_hit(t_sprint *sprint) {
    if (!sprint->object->is_active || --sprint->health > 0) {
        return;
    }
    spawn_sprint_tasks(sprint);
    sprint->object->is_active = false;
}

bool endgame(void) {
    t_sprint *sprints = sprints_get();
    t_task *tasks = tasks_get();
    for (int i = 0; i < MAX_SPRINTS; i++) {
        for (int j = 0; j < MAX_TASKS; j++) {
            if (sprints[i].object->is_active) {
                return false;
            }
            if (tasks[j].object->is_active) {
                return false;
            }
        }
    }
    return true;
}
