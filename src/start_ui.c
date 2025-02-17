#include "../inc/start_ui.h"
#include "../inc/gameobject.h"
#include "../inc/bee.h"

bool renderStartScreen(void) {
    SDL_Event event;
    while (true) {
        SDL_Renderer *renderer = game_get()->renderer;
        TTF_Font *font = game_get()->font;
        SDL_Texture *beeTexture = get_bee()->object->texture;

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color black = {0, 0, 0, 255};

        SDL_Rect buttonRect_start = {WINDOW_WIDTH / 2 - 100,
                                     WINDOW_HEIGHT / 2 - 200,
                                     200,
                                     50};

        SDL_Rect buttonRect_exit = {WINDOW_WIDTH / 2 - 100,
                                    WINDOW_HEIGHT / 2 + 225,
                                    200,
                                    50};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Surface *titleSurface =
            TTF_RenderText_Solid(font, "Deadlines Rule the World", white);
        SDL_Texture *titleTexture =
            SDL_CreateTextureFromSurface(renderer, titleSurface);
        SDL_Rect titleRect = {WINDOW_WIDTH / 2 - titleSurface->w / 2,
                              50,
                              titleSurface->w,
                              titleSurface->h};
        SDL_FreeSurface(titleSurface);
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
        SDL_DestroyTexture(titleTexture);

        SDL_Surface *sloganSurface =
            TTF_RenderText_Solid(font,
                                 "Click \"Start\" to begin your own Marathon!",
                                 white);
        SDL_Texture *sloganTexture =
            SDL_CreateTextureFromSurface(renderer, sloganSurface);
        SDL_Rect sloganRect = {WINDOW_WIDTH / 2 - sloganSurface->w / 2,
                               100,
                               sloganSurface->w,
                               sloganSurface->h};
        SDL_FreeSurface(sloganSurface);
        SDL_RenderCopy(renderer, sloganTexture, NULL, &sloganRect);
        SDL_DestroyTexture(sloganTexture);

        SDL_SetRenderDrawColor(renderer, 255, 204, 0, 255);
        SDL_RenderFillRect(renderer, &buttonRect_start);
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Start", black);
        SDL_Texture *textTexture =
            SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {
            buttonRect_start.x + (buttonRect_start.w - textSurface->w) / 2,
            buttonRect_start.y + (buttonRect_start.h - textSurface->h) / 2,
            textSurface->w,
            textSurface->h};
        SDL_FreeSurface(textSurface);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);

        SDL_Rect beeRect = {WINDOW_WIDTH / 2 - 50,
                            WINDOW_HEIGHT / 2 - 50,
                            100,
                            100};
        SDL_RenderCopy(renderer, beeTexture, NULL, &beeRect);

        SDL_SetRenderDrawColor(renderer, 178, 34, 34, 255);
        SDL_RenderFillRect(renderer, &buttonRect_exit);
        SDL_Surface *textSurface_exit =
            TTF_RenderText_Solid(font, "Exit", black);
        SDL_Texture *textTexture_exit =
            SDL_CreateTextureFromSurface(renderer, textSurface_exit);
        SDL_Rect textRect_exit = {
            buttonRect_exit.x + (buttonRect_exit.w - textSurface_exit->w) / 2,
            buttonRect_exit.y + (buttonRect_exit.h - textSurface_exit->h) / 2,
            textSurface_exit->w,
            textSurface_exit->h};
        SDL_RenderCopy(renderer, textTexture_exit, NULL, &textRect_exit);
        SDL_FreeSurface(textSurface_exit);
        SDL_DestroyTexture(textTexture_exit);

        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= buttonRect_start.x &&
                    x <= buttonRect_start.x + buttonRect_start.w &&
                    y >= buttonRect_start.y &&
                    y <= buttonRect_start.y + buttonRect_start.h) {
                    SDL_FlushEvent(SDL_MOUSEBUTTONDOWN);
                    objects_purge();
                    return true;
                }

                if (x >= buttonRect_exit.x &&
                    x <= buttonRect_exit.x + buttonRect_exit.w &&
                    y >= buttonRect_exit.y &&
                    y <= buttonRect_exit.y + buttonRect_exit.h) {
                    exit(0);
                }
            }
        }
    }
}

int renderPauseScreen(void) {
    SDL_Event event;
    while (true) {
        SDL_Renderer *renderer = game_get()->renderer;
        TTF_Font *font = game_get()->font;

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color black = {0, 0, 0, 255};
        SDL_Color green = {50, 205, 50, 255};
        SDL_Color red = {178, 34, 34, 255};

        SDL_Rect buttonYes = {WINDOW_WIDTH / 2 - 110,
                              WINDOW_HEIGHT / 2,
                              100,
                              50};
        SDL_Rect buttonNo = {WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT / 2, 100, 50};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
        SDL_RenderClear(renderer);

        SDL_Surface *pauseSurface = TTF_RenderText_Solid(font, "Pause", white);
        SDL_Texture *pauseTexture =
            SDL_CreateTextureFromSurface(renderer, pauseSurface);
        SDL_Rect pauseRect = {WINDOW_WIDTH / 2 - pauseSurface->w / 2,
                              50,
                              pauseSurface->w,
                              pauseSurface->h};
        SDL_FreeSurface(pauseSurface);
        SDL_RenderCopy(renderer, pauseTexture, NULL, &pauseRect);
        SDL_DestroyTexture(pauseTexture);

        SDL_Surface *menuSurface =
            TTF_RenderText_Solid(font, "Return to Menu?", white);
        SDL_Texture *menuTexture =
            SDL_CreateTextureFromSurface(renderer, menuSurface);
        SDL_Rect menuRect = {WINDOW_WIDTH / 2 - menuSurface->w / 2,
                             120,
                             menuSurface->w,
                             menuSurface->h};
        SDL_FreeSurface(menuSurface);
        SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);
        SDL_DestroyTexture(menuTexture);

        SDL_SetRenderDrawColor(renderer, green.r, green.g, green.b, green.a);
        SDL_RenderFillRect(renderer, &buttonYes);
        SDL_Surface *yesSurface = TTF_RenderText_Solid(font, "Yes", black);
        SDL_Texture *yesTexture =
            SDL_CreateTextureFromSurface(renderer, yesSurface);
        SDL_Rect yesRect = {buttonYes.x + (buttonYes.w - yesSurface->w) / 2,
                            buttonYes.y + (buttonYes.h - yesSurface->h) / 2,
                            yesSurface->w,
                            yesSurface->h};
        SDL_FreeSurface(yesSurface);
        SDL_RenderCopy(renderer, yesTexture, NULL, &yesRect);
        SDL_DestroyTexture(yesTexture);

        SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
        SDL_RenderFillRect(renderer, &buttonNo);
        SDL_Surface *noSurface = TTF_RenderText_Solid(font, "No", black);
        SDL_Texture *noTexture =
            SDL_CreateTextureFromSurface(renderer, noSurface);
        SDL_Rect noRect = {buttonNo.x + (buttonNo.w - noSurface->w) / 2,
                           buttonNo.y + (buttonNo.h - noSurface->h) / 2,
                           noSurface->w,
                           noSurface->h};
        SDL_FreeSurface(noSurface);
        SDL_RenderCopy(renderer, noTexture, NULL, &noRect);
        SDL_DestroyTexture(noTexture);

        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x >= buttonYes.x && x <= buttonYes.x + buttonYes.w &&
                    y >= buttonYes.y && y <= buttonYes.y + buttonYes.h) {
                    return 0;
                }

                if (x >= buttonNo.x && x <= buttonNo.x + buttonNo.w &&
                    y >= buttonNo.y && y <= buttonNo.y + buttonNo.h) {
                    return 1;
                }
            }
        }
    }
}
