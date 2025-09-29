#ifndef INPUT_H
#define INPUT_H

#include "list.h"
#include <stdint.h>

typedef struct EventManager {
    ArrayHeader *events_header;
    SDL_Event *events_list;
} EventManager;

extern EventManager *event_mg;

EventManager *init_event_manager(void);
void destroy_event_manager(void);
void poll_events(void);

#endif
