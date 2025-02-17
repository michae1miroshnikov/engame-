#include "../inc/bee.h"
#include "../inc/engine.h"

bool handleEvents(void) {
    SDL_Event event;
    t_bee *bee = get_bee();

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                return false;
            case SDL_WINDOWEVENT:
                // TODO: DO SOMETHING
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    int pauseActive = renderPauseScreen();
                    if (pauseActive == 0) {
                        return false;
                        break;
                    }
                    else if (pauseActive == 1) {
                        reset_bee();
                        break;
                    }
                }
                if (event.key.keysym.sym == SDLK_F11) {
                    toggle_fullscreen(game_get()->window);
                }
                if (event.key.keysym.sym == SDLK_SPACE && bee->can_shoot) {
                    bee->next_missile = get_next_missile(bee->missiles);
                    bee->missiles[bee->next_missile].object->x = bee->object->x;
                    bee->missiles[bee->next_missile].object->y = bee->object->y;
                    bee->missiles[bee->next_missile].object->angle =
                        bee->object->angle;
                    shoot(&bee->missiles[bee->next_missile]);
                    bee->can_shoot = false;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_SPACE) {
                    bee->can_shoot = true;
                }
                break;
            default:
                break;
        }
    }
    return true;
}
