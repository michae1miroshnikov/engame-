#include "../inc/engine.h"
#include "../inc/game.h"
#include "../inc/gameobject.h"

static void cleanup_textures(void) {
    for (int i = 0; i < MAX_TEXTURE_CACHE; i++) {
        if (textureCache[i].texture) {
            SDL_DestroyTexture(textureCache[i].texture);
            textureCache[i].texture = NULL;
            textureCache[i].path[0] = '\0';
        }
    }
}

void cleanup(void) {
    cleanup_textures();
    SDL_DestroyRenderer(game_get()->renderer);
    SDL_DestroyWindow(game_get()->window);
    // TODO: CLEANUP FONT (MOVE IT INTO GAME GET)
    IMG_Quit();
    SDL_Quit();
}
