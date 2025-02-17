#include "../inc/handle_events.h"
#include "../inc/bee.h"

t_event_state *get_event_state(void) {
    static t_event_state event;
    static bool initialized;

    if (!initialized) {
        event = event_state_new();
        initialized = true;
    }

    return &event;
}

t_event_state event_state_new(void) {
    t_event_state state;
    state.next_event_time =
        SDL_GetTicks() + MIN_EVENT_INTERVAL +
        (rand() % (MAX_EVENT_INTERVAL - MIN_EVENT_INTERVAL));
    state.event_end_time = 0;
    state.active_event = EVENT_NONE;
    state.enemy_speed_multiplier = 1.0;
    state.enemies_can_shoot = false;
    state.is_text_active = false;

    return state;
}

void start_random_event(void) {
    t_event_state *event_state = get_event_state();
    int random_event = 1; // add new rand values when add new events

    switch (random_event) {
        case EVENT_SPEEDUP_ENEMIES:
            event_state->active_event = EVENT_SPEEDUP_ENEMIES;
            event_state->enemy_speed_multiplier = SPEED_BOOST;
            event_state->event_end_time =
                SDL_GetTicks() + (10000 + rand() % 5000);
            event_state->is_text_active = true;
            SDL_Log("Speed up enemies");
            break;

        default:
            event_state->active_event = EVENT_NONE;
            break;
    }
}

void end_event(void) {
    t_event_state *event_state = get_event_state();
    event_state->active_event = EVENT_NONE;
    event_state->enemy_speed_multiplier = 1.0;
    event_state->enemies_can_shoot = false;
    event_state->is_text_active = false;
    event_state->next_event_time =
        SDL_GetTicks() + MIN_EVENT_INTERVAL +
        (rand() % (MAX_EVENT_INTERVAL - MIN_EVENT_INTERVAL));
    SDL_Log("End of event");
}

void update_events(void) {
    t_event_state *event_state = get_event_state();
    Uint32 current_time = SDL_GetTicks();

    if (event_state->active_event == EVENT_NONE &&
        current_time >= event_state->next_event_time) {
        start_random_event();
    }
    else if (event_state->active_event != EVENT_NONE &&
             current_time >= event_state->event_end_time) {
        end_event();
    }
    render_deadline_message();
}

void render_deadline_message(void) {
    SDL_Renderer *renderer = game_get()->renderer;
    t_event_state *event_state = get_event_state();
    if (event_state->active_event == EVENT_SPEEDUP_ENEMIES &&
        event_state->is_text_active) {
        SDL_Color textColor = {255, 0, 0, 255};
        const char *message = "DEADLINE!!!";

        if (!game_get()->font) {
            SDL_Log("Font is not loaded.");
            return;
        }

        SDL_Surface *textSurface =
            TTF_RenderText_Solid(game_get()->font, message, textColor);
        if (!textSurface) {
            SDL_Log("Failed to render text! TTF_Error: %s", TTF_GetError());
            return;
        }

        SDL_Texture *textTexture =
            SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            SDL_Log("Failed to create texture from text! SDL_Error: %s",
                    SDL_GetError());
            SDL_FreeSurface(textSurface);
            return;
        }

        SDL_Rect textRect = {WINDOW_WIDTH / 2 - textSurface->w / 2,
                             WINDOW_HEIGHT - 50,
                             textSurface->w,
                             textSurface->h};

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
}
