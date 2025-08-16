#ifndef INPUT_H
#define INPUT_H

#include "list.h"

typedef struct input_manager {
    array_header_t *events_header;
    SDL_Event *events_list;
} input_manager_t;

input_manager_t *init_input_manager(void);
uint8_t poll_events(input_manager_t *in_mg);

#endif
