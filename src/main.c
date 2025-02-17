#include "../inc/engine.h"
#include "../inc/game.h"

int main(void) {
    if (renderStartScreen()) {
        gameLoop();
    }
    cleanup();
    return 0;
}
