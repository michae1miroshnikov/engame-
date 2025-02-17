#include "../inc/background.h"
#include "../inc/bee.h"
#include "../inc/engine.h"
#include "../inc/start_ui.h"
#include "../inc/bee.h"
#include "../inc/game_over.h"

void gameLoop(void) {
    srand(time(NULL));
    while (renderStartScreen()) {
        init_stars();
        sprints_spawn();
        Uint32 victory_time = 0;
        while (get_bee()->object->is_active) {
            Uint32 frameStart = SDL_GetTicks();
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (!handleEvents()) {
                break;
            }
            updateGameState(state);
            renderGame();
            if (endgame()) {
                if (victory_time == 0) {
                    victory_time = SDL_GetTicks();
                }
                else if (SDL_GetTicks() - victory_time >= 5000) {
                    break;
                }
            }
            controlFrameRate(frameStart);
        }
    }
}
