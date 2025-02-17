#include "../inc/game.h"

static SDL_Window *createWindow(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("Deadlines rule the world",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          // SDL_WINDOW_FULLSCREEN_DESKTOP |
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    return window;
}

void toggle_fullscreen(SDL_Window *window) {
    Uint32 flags = SDL_GetWindowFlags(window);
    if (flags & SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen(window, 0);
    }
    else {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
}

static SDL_Renderer *createRenderer(SDL_Window *window) {
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, 0); // use 0 as it is the safest option
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    return renderer;
}

static TTF_Font *create_font(void) {
    if (TTF_Init() < 0) {
        SDL_Log("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }

    TTF_Font *font = TTF_OpenFont("resource/font.ttf", 36);
    if (!font) {
        SDL_Log("TTF_OpenFont: %s\n", TTF_GetError());
        exit(1);
    }
    return font;
}

static t_game game_new(void) {
    t_game game;
    game.window = createWindow();
    game.renderer = createRenderer(game.window);
    game.font = create_font();
    return game;
}

t_game *game_get(void) {
    static t_game game;
    static bool initialized = false;

    if (!initialized) {
        game = game_new();
        initialized = true;
    }

    return &game;
}
