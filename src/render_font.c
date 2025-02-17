#include "../inc/gamelib.h"
#include "../inc/game.h"

void render_font(void) {
    SDL_Renderer *renderer = game_get()->renderer;
    TTF_Font *font = game_get()->font;
    if (!renderer || !font) {
        SDL_Log("Renderer or font is NULL in render_font");
        return;
    }

    t_bee *bee = get_bee();

    char scoreText[32];
    snprintf(scoreText, 32, "Score: %d", bee->coins);
    SDL_Color textColor = {255, 255, 255, 255};

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    if (!textSurface) {
        SDL_Log("Failed to render score text! TTF_Error: %s", TTF_GetError());
        return;
    }
    SDL_Texture *textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_Log("Failed to create texture from score text! SDL_Error: %s",
                SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect scoreRect = {10, 10, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &scoreRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    char staminaText[32];
    snprintf(staminaText, 32, "Stamina: ");
    textSurface = TTF_RenderText_Solid(font, staminaText, textColor);
    if (!textSurface) {
        SDL_Log("Failed to render stamina text! TTF_Error: %s", TTF_GetError());
        return;
    }
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_Log("Failed to create texture from stamina text! SDL_Error: %s",
                SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect staminaTextRect = {10, 50, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &staminaTextRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);

    SDL_Rect staminaBarOutline = {10, 90, 100, 20};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &staminaBarOutline);

    SDL_Rect staminaBarFill = {12, 92, (int)(96 * (bee->stamina / 100.0)), 16};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &staminaBarFill);
}

void render_victory_text(void) {
    SDL_Renderer *renderer = game_get()->renderer;
    TTF_Font *font = game_get()->font;

    if (!renderer || !font) {
        SDL_Log("Renderer or font is NULL in render_victory_text");
        return;
    }

    const char *victory_text = "You pass the innovation campus!";
    SDL_Color text_color = {0, 255, 0, 255};

    SDL_Surface *textSurface =
        TTF_RenderText_Solid(font, victory_text, text_color);
    if (!textSurface) {
        SDL_Log("Failed to render victory text! TTF_Error: %s", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture =
        SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_Log("Failed to create texture from victory text! SDL_Error: %s",
                SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    int winWidth;
    int winHeight;
    SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);

    SDL_Rect textRect = {winWidth / 2 - textSurface->w / 2,
                         winHeight / 2 - textSurface->h / 2,
                         textSurface->w,
                         textSurface->h};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}
