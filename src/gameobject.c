#include "../inc/gameobject.h"
#include "../inc/bee.h"

static int *objects_get_next_index(void) {
    static int index = 0;
    index = index % MAX_OBJECTS;
    return &index;
}

int objects_length(void) {
    return *objects_get_next_index();
}

static void object_reset(t_gameobject *object) {
    object->is_active = false;
    object->angle = 0;
    object->speed = 0;
    object->x = 0;
    object->y = 0;
    object->width = 0;
    object->height = 0;
    object->texture = NULL;
}

static t_gameobject object_create(void) {
    t_gameobject object;
    object_reset(&object);
    return object;
}

t_gameobject *objects_get(void) {
    static t_gameobject object[MAX_OBJECTS] = {0};
    static bool is_initialized = false;
    for (int i = 0; !is_initialized && i < MAX_OBJECTS; i++) {
        object[i] = object_create();
    }
    is_initialized = true;

    return object;
}

t_gameobject *object_new(void) {
    return &objects_get()[(*objects_get_next_index())++];
}

void objects_purge(void) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        object_reset(&objects_get()[i]);
    }
    *objects_get_next_index() = 0;
    *reset_bee() = true;
    *reset_tasks() = true;
    *reset_sprints() = true;
    *reset_coins() = true;
}
