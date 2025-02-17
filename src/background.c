#include "../inc/background.h"

void init_stars(void) {
    t_gameobject *stars[MAX_STARS] = {0};
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i] = object_new();
        stars[i]->x = rand() % WINDOW_WIDTH;
        stars[i]->y = rand() % WINDOW_HEIGHT;
        stars[i]->width = 2 + rand() % 5;
        stars[i]->height = stars[i]->width;
        stars[i]->speed = STAR_SPEED;
        stars[i]->angle = rand() % 360;
        stars[i]->is_active = true;
        stars[i]->type = GAMEOBJECT_STAR;
    }
}
