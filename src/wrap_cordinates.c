#include "../inc/gamelib.h"
#include "../inc/game.h"
#include "../inc/gameobject.h"

void wrapCoordinates(t_gameobject *object) {
    bool is_wrapped = false;
    if (object->x < -50) {
        object->x = WINDOW_WIDTH - 10;
        is_wrapped = true;
    }
    else if (object->x > WINDOW_WIDTH) {
        object->x = -40;
        is_wrapped = true;
    }

    if (object->y < -50) {
        object->y = WINDOW_HEIGHT - 50;
        is_wrapped = true;
    }
    else if (object->y > WINDOW_HEIGHT) {
        object->y = -40;
        is_wrapped = true;
    }

    if (object->type == GAMEOBJECT_MISSILE && is_wrapped) {
        object->is_active = false;
    }
}
