#include "../inc/game_over.h"

static void clearScreen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

static void drawCenteredMessage(SDL_Renderer *renderer,
                                TTF_Font *font,
                                SDL_Color color,
                                int winWidth,
                                int winHeight) {
    SDL_Surface *game_over_surface =
        TTF_RenderText_Solid(font, GAME_OVER_TEXT, color);
    SDL_Texture *game_over_texture =
        SDL_CreateTextureFromSurface(renderer, game_over_surface);
    SDL_Rect game_over_rect;
    game_over_rect.x = winWidth / 2 - game_over_surface->w / 2;
    game_over_rect.y = winHeight / 2 - game_over_surface->h / 2;
    game_over_rect.w = game_over_surface->w;
    game_over_rect.h = game_over_surface->h;

    SDL_RenderCopy(renderer, game_over_texture, NULL, &game_over_rect);
    SDL_FreeSurface(game_over_surface);
    SDL_DestroyTexture(game_over_texture);
}

static void drawExitPrompt(SDL_Renderer *renderer,
                           TTF_Font *font,
                           SDL_Color color,
                           int winHeight) {
    SDL_Surface *e_for_exit_surface =
        TTF_RenderText_Solid(font, E_FOR_EXIT_TEXT, color);
    SDL_Texture *e_for_exit_texture =
        SDL_CreateTextureFromSurface(renderer, e_for_exit_surface);
    SDL_Rect e_for_exit_rect;
    e_for_exit_rect.x = 10;
    e_for_exit_rect.y = winHeight - e_for_exit_surface->h - 10;
    e_for_exit_rect.w = e_for_exit_surface->w;
    e_for_exit_rect.h = e_for_exit_surface->h;

    SDL_RenderCopy(renderer, e_for_exit_texture, NULL, &e_for_exit_rect);
    SDL_FreeSurface(e_for_exit_surface);
    SDL_DestroyTexture(e_for_exit_texture);
}

static void drawRestartPrompt(SDL_Renderer *renderer,
                              TTF_Font *font,
                              SDL_Color color,
                              int winWidth,
                              int winHeight) {
    SDL_Surface *r_for_restart_surface =
        TTF_RenderText_Solid(font, R_FOR_RESTART_TEXT, color);
    SDL_Texture *r_for_restart_texture =
        SDL_CreateTextureFromSurface(renderer, r_for_restart_surface);
    SDL_Rect r_for_restart_rect;
    r_for_restart_rect.x = winWidth - r_for_restart_surface->w - 10;
    r_for_restart_rect.y = winHeight - r_for_restart_surface->h - 10;
    r_for_restart_rect.w = r_for_restart_surface->w;
    r_for_restart_rect.h = r_for_restart_surface->h;

    SDL_RenderCopy(renderer, r_for_restart_texture, NULL, &r_for_restart_rect);
    SDL_FreeSurface(r_for_restart_surface);
    SDL_DestroyTexture(r_for_restart_texture);
}

bool game_over(void) {
    SDL_Renderer *renderer = game_get()->renderer;
    TTF_Font *font = game_get()->font;
    SDL_Color text_color = {255, 255, 255, 255};

    clearScreen(renderer);

    int winWidth, winHeight;
    SDL_GetRendererOutputSize(renderer, &winWidth, &winHeight);

    drawCenteredMessage(renderer, font, text_color, winWidth, winHeight);
    drawExitPrompt(renderer, font, text_color, winHeight);
    drawRestartPrompt(renderer, font, text_color, winWidth, winHeight);

    SDL_RenderPresent(renderer);

    return true;
}
