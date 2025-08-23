#ifndef INPUT_H
#define INPUT_H

#include "list.h"

#define is_done(input) ~input & (1 << 7)

typedef struct event_manager {
    array_header_t *events_header;
    SDL_Event *events_list;
} event_manager_t;

extern event_manager_t *event_mg;

event_manager_t *init_event_manager(void);
void destroy_event_manager(void);
void poll_events(void);
uint16_t recieve_input();

#endif
