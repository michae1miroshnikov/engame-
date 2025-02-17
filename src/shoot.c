#include "../inc/gamelib.h"
#include "SDL2/SDL_log.h"
#include "../inc/gameobject.h"
#include "../inc/missile.h"
#include "../inc/bee.h"

void shoot(t_missile *missile) {
    double centerX = missile->object->x + (RECT_SIZE / 2);
    double centerY = missile->object->y + (RECT_SIZE / 2);

    double radians = missile->object->angle * M_PI / 180.0;
    double offsetY = (RECT_SIZE / 1.5) * cos(radians);
    double offsetX = (RECT_SIZE / 2) * sin(radians);

    missile->object->x = centerX + offsetX;
    missile->object->y = centerY - offsetY;
    missile->object->speed = MISSILE_SPEED;
    missile->object->is_active = true;
    missile->lifetime = SDL_GetTicks() + 5000;
    missile->spawn_time = SDL_GetTicks();
    missile->object->type = GAMEOBJECT_MISSILE;
}

void updateMissiles(void) {
    t_bee *bee = get_bee();
    for (int i = 0; i < MAX_MISSILES; i++) {
        if (bee->missiles[i].object->is_active) {
            if (SDL_GetTicks() > bee->missiles[i].lifetime) {
                bee->missiles[i].object->is_active = false;
            }
        }
    }
}

int get_next_missile(t_missile *missiles) {
    int index = get_bee()->next_missile;
    for (int i = index; (i + 1) % MAX_MISSILES != index;) {
        if (!missiles[i].object->is_active) {
            index = i;
            return index;
        }
        i = (i + 1) % MAX_MISSILES;
    }
    index = (index + 1) % MAX_MISSILES;
    return index;
}
