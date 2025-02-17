#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "missile.h"
#include "movement.h"
#include "bee.h"
#include "handle_events.h"


typedef struct s_sprint t_sprint;
typedef struct s_task t_task;

#define DEBUG 0
#define FPS 60 
#define M_PI 3.14159265358979323846

SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *path);
bool handleEvents(void);
void updateGameState(const Uint8 *keyState);
void renderGame(void);
void render_font(void);
void render_victory_text(void);
void controlFrameRate(Uint32 frameStart);
void gameLoop(void);
void cleanup(void);
