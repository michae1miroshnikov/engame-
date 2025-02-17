#ifndef HANDLE_EVENTS_H
#define HANDLE_EVENTS_H

#include "gameobject.h"
#include "coin.h"
#include "SDL2/SDL_log.h"

#define MIN_EVENT_INTERVAL 30000  // 30 s
#define MAX_EVENT_INTERVAL 45000  // 45 s
#define MIN_ENEMY_SHOOT_TIME 3000  // 3 s
#define MAX_ENEMY_SHOOT_TIME 5000  // 5 s
#define SPEED_BOOST 2.3            //Enemies boost

typedef enum {
    EVENT_NONE,
    EVENT_SPEEDUP_ENEMIES,
    EVENT_ENEMY_SHOOTS,
    EVENT_RANDOM
} t_game_event;

typedef struct s_event_state{
    Uint32 next_event_time;
    Uint32 event_end_time;
    t_game_event active_event;
    float enemy_speed_multiplier;
    bool enemies_can_shoot;
    bool is_text_active;
} t_event_state;

t_event_state event_state_new(void);
t_event_state *get_event_state(void);
void start_random_event(void);
void end_event(void);
void update_events(void);
void render_deadline_message(void);

#endif
