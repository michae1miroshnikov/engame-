#pragma once 

#include <SDL2/SDL_render.h>
#include <stdbool.h>


#define MAX_OBJECTS 350

typedef enum e_gameobject_type {
    GAMEOBJECT_BEE,
    GAMEOBJECT_MISSILE,
    GAMEOBJECT_SPRINT,
    GAMEOBJECT_TASK,
    GAMEOBJECT_COIN,
    GAMEOBJECT_STAR
}            t_gameobject_type;

typedef struct s_gameobject {
    double x;
    double y;
    double width;
    double height;
    double speed;
    double angle;
    bool is_active;
    Uint32 spawn_time;
    SDL_Texture *texture;
    t_gameobject_type type;
}              t_gameobject;

t_gameobject *objects_get(void);
t_gameobject *object_new(void);
int objects_length(void);
void objects_purge(void);
