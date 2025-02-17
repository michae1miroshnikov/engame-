#include "../inc/gamelib.h"
#include "SDL2/SDL_log.h"
#include "../inc/game.h"
#include "../inc/gameobject.h"
#include "../inc/sprint.h"

void drawCircle(int centerX, int centerY, int radius) {
    for (int width = -radius; width <= radius; width++) {
        for (int height = -radius; height <= radius; height++) {
            if (width * width + height * height <= radius * radius) {
                SDL_RenderDrawPoint(game_get()->renderer,
                                    centerX + width,
                                    centerY + height);
            }
        }
    }
}

static void render_flame(void) {
    t_bee *bee = get_bee();

    if (!bee->flame_texture || bee->stamina <= 0) {
        return;
    }

    SDL_Renderer *renderer = game_get()->renderer;

    int flameWidth = 20;
    int flameHeight = 40;

    double radians = (bee->object->angle + 180) * M_PI / 180.0;

    int beeCenterX = bee->object->x + bee->object->width / 2;
    int beeCenterY = bee->object->y + bee->object->height / 2;

    int offsetY = bee->object->height / 2 + flameHeight / 2;

    int flameX = beeCenterX - flameWidth / 2 + offsetY * sin(radians);
    int flameY = beeCenterY - flameHeight / 2 - offsetY * cos(radians);

    SDL_Rect flameRect = {(int)flameX, (int)flameY, flameWidth, flameHeight};

    SDL_RenderCopyEx(renderer,
                     bee->flame_texture,
                     NULL,
                     &flameRect,
                     bee->object->angle + 180,
                     NULL,
                     SDL_FLIP_NONE);
}

void renderGame(void) {
    t_bee *bee = get_bee();
    t_gameobject *objects = objects_get();

    SDL_SetRenderDrawColor(game_get()->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game_get()->renderer);

    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].is_active) {
            continue;
        }
        SDL_Rect hitbox = {(int)objects[i].x,
                           (int)objects[i].y,
                           (int)objects[i].width,
                           (int)objects[i].height};
        SDL_Point center = {objects[i].width / 2, objects[i].height / 2};

        if (DEBUG) {
            double radius =
                sqrt(pow(objects[i].width, 2) + pow(objects[i].height, 2)) / 2;
            SDL_SetRenderDrawColor(game_get()->renderer, 0, 0, 255, 255);
            drawCircle((int)objects[i].x + (objects[i].width / 2.0),
                       (int)objects[i].y + (objects[i].height / 2.0),
                       radius);
        }
        if (objects[i].texture) {
            // FIXME: to choose render function
            SDL_RenderCopyEx(game_get()->renderer,
                             objects[i].texture,
                             NULL,
                             &hitbox,
                             objects[i].angle,
                             &center,
                             SDL_FLIP_NONE);
        }
        else if (objects[i].type == GAMEOBJECT_MISSILE) {
            SDL_SetRenderDrawColor(game_get()->renderer, 255, 255, 255, 255);
            drawCircle((int)objects[i].x, (int)objects[i].y, MISSILE_SIZE);
        }
        else if (objects[i].type == GAMEOBJECT_SPRINT) {
            SDL_SetRenderDrawColor(game_get()->renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(game_get()->renderer, &hitbox);
        }
        else if (objects[i].type == GAMEOBJECT_TASK) {
            SDL_SetRenderDrawColor(game_get()->renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(game_get()->renderer, &hitbox);
        }
        else if (objects[i].type == GAMEOBJECT_STAR) {
            t_event_state *event_state = get_event_state();
            if (event_state->active_event == EVENT_SPEEDUP_ENEMIES) {
                SDL_SetRenderDrawColor(game_get()->renderer, 255, 0, 0, 70);
            }
            else {
                SDL_SetRenderDrawColor(game_get()->renderer, 200, 200, 200, 40);
            }
            SDL_SetRenderDrawBlendMode(game_get()->renderer,
                                       SDL_BLENDMODE_BLEND);
            drawCircle(objects[i].x, objects[i].y, objects[i].width / 2);
        }
    }
    render_font();
    if (bee->is_boosting) {
        render_flame();
    }
    if (endgame()) {
        render_victory_text();
    }
    SDL_RenderPresent(game_get()->renderer);
}
