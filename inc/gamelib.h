#ifndef GAMELIB_H
#define GAMELIB_H

#include "sprint.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include "handle_events.h"
#include "engine.h"
#include "movement.h"
#include "background.h"
#include "start_ui.h"
#define RECT_SIZE 50
#define FPS 60 
// #define M_PI 3.14159265358979323846
typedef struct {
    char path[256];
    SDL_Texture *texture;
} t_texture_entry;

#define MAX_TEXTURE_CACHE 64
static t_texture_entry textureCache[MAX_TEXTURE_CACHE];
void wrapCoordinates(t_gameobject *object);
void moveObjects(const Uint8 *keyState);
void drawCircle(int centerX, int centerY, int radius);

#endif
