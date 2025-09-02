#ifndef INPUT_H
#define INPUT_H

#include "list.h"
#include <stdint.h>

typedef enum Input {
    INPUT_QUIT,
    INPUT_Z_KEY,
    INPUT_X_KEY,
    INPUT_RIGHT,
    INPUT_LEFT,
    INPUT_UP,
    INPUT_DOWN,
} Input;

#define IS_DOWN(input) ~input & INPUT_QUIT

typedef struct EventManager {
    ArrayHeader *events_header;
    SDL_Event *events_list;
    ArrayHeader *inputs;
} EventManager;

typedef struct InputEvent {
    Input input;
    Uint64 time_stamp;
} InputEvent;

extern EventManager *event_mg;

EventManager *init_event_manager(void);
void destroy_event_manager(void);
void poll_events(void);
void recieve_input(void);

#endif
