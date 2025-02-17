#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_FLAGS (SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP)
typedef struct s_game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
}              t_game; 

t_game *game_get(void);
void toggle_fullscreen(SDL_Window *window);
