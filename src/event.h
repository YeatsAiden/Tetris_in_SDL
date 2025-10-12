#ifndef EVENT_H
#define EVENT_H

#include "list.h"
#include <stdint.h>

typedef struct EventManager {
    ArrayHeader *events_header;
    SDL_Event *events_list;
    uint8_t quit;
} EventManager;

extern EventManager *event_mg;

EventManager *init_event_manager(void);
void destroy_event_manager(void);
void poll_events(void);

#endif
