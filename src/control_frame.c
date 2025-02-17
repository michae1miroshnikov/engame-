#include "../inc/engine.h"

void controlFrameRate(Uint32 frameStart) {
    int frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < 1000 / FPS) {
        SDL_Delay(1000 / FPS - frameTime);
    }
}
