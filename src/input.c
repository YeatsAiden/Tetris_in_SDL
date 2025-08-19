#include <SDL2/SDL.h>
#include <stdlib.h>

#include "input.h"
#include "list.h"

input_manager_t *in_mg = NULL;

input_manager_t *init_input_manager(void){
    in_mg = malloc(sizeof(input_manager_t));

    if (in_mg == NULL) return NULL;

    in_mg->events_header = Init_Array_Header(&in_mg->events_header, SDL_Event, 32);
    in_mg->events_list = Array(in_mg->events_header, SDL_Event);

    return in_mg;
}

void destroy_input_manager(void){
    free(in_mg->events_header);
    free(in_mg);
}

uint8_t poll_events(void){
    SDL_Event event;
    uint8_t flags = 0;
    reset_array(in_mg->events_header);

    while (SDL_PollEvent(&event)) {
        append(in_mg->events_header, &event);
        in_mg->events_list = Array(in_mg->events_header, SDL_Event); //just in case the array is resized

        switch (event.type) {
            case SDL_QUIT:
                flags = flags | 0b0001;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) flags = flags | 0b0001;
                break;
        }
    }

    return flags;
}
