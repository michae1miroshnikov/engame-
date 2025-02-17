#include "../inc/bee.h"
#include "../inc/game.h"
#include "../inc/gamelib.h"
#include "SDL2/SDL_log.h"

static t_bee bee_new(void) {
    t_bee bee;
    bee.coins = 0;
    bee.next_missile = 0;
    bee.can_shoot = true;
    bee.object = object_new();
    bee.object->type = GAMEOBJECT_BEE;
    bee.object->speed = MAX_MOVEMENT_SPEED;
    bee.object->width = RECT_SIZE;
    bee.object->height = RECT_SIZE;
    bee.object->x = (WINDOW_WIDTH - RECT_SIZE) / 2.0;
    bee.object->y = (WINDOW_HEIGHT - RECT_SIZE) / 2.0;
    bee.object->is_active = true;
    bee.is_boosting = false;
    bee.object->angle = 0;
    bee.movement.speedX = 0;
    bee.movement.speedY = 0;
    bee.movement.rotationSpeed = ROTATION_SPEED;
    bee.movement.acceleration = MOVEMENT_ACCELERATION;
    bee.movement.maxSpeed = MAX_MOVEMENT_SPEED;
    bee.movement.deceleration = MOVEMENT_DECELERATION;
    bee.movement.boostFactor = BOOST_FACTOR;
    bee.stamina = 100.0;

    for (int i = 0; i < MAX_MISSILES; i++) {
        bee.missiles[i].object = object_new();
        bee.missiles[i].object->type = GAMEOBJECT_MISSILE;
    }
    bee.object->texture =
        loadTexture(game_get()->renderer, "./resource/sprites/bee.png");
    if (!bee.object->texture) {
        SDL_LogWarn(SDL_LOG_CATEGORY_ERROR, "Failed to find bee texture");
        exit(1);
    }

    bee.flame_texture =
        loadTexture(game_get()->renderer, "./resource/sprites/flame.png");
    if (!bee.flame_texture) {
        SDL_LogWarn(SDL_LOG_CATEGORY_ERROR, "Failed to find flame texture");
        exit(1);
    }
    return bee;
}

t_bee *get_bee(void) {
    static t_bee bee;

    if (*reset_bee()) {
        bee = bee_new();
        *reset_bee() = false;
    }

    return &bee;
}

// todo: do we need to reset missiles somehow?
bool *reset_bee(void) {
    static bool reset = true;
    return &reset;
}
