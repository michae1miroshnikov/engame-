#include "../inc/gamelib.h"
#include <string.h>

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path) {
    for (int i = 0; i < MAX_TEXTURE_CACHE; i++) {
        if (textureCache[i].texture &&
            strcmp(textureCache[i].path, path) == 0) {
            return textureCache[i].texture;
        }
    }

    SDL_Surface *surface = IMG_Load(path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    for (int i = 0; i < MAX_TEXTURE_CACHE; i++) {
        if (!textureCache[i].texture) {
            strncpy(textureCache[i].path, path, sizeof(textureCache[i].path));
            textureCache[i].texture = texture;
            break;
        }
    }

    return texture;
}
