#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <stdint.h>
#include <stdlib.h>

#include "event.h"
#include "list.h"

EventManager *event_mg = NULL;

EventManager *init_event_manager(void){
    event_mg = malloc(sizeof(EventManager));

    if (event_mg == NULL) return NULL;

    event_mg->events_header = Init_Array_Header(&event_mg->events_header, SDL_Event, 32);
    event_mg->events_list = Array(event_mg->events_header, SDL_Event);

    return event_mg;
}

void destroy_event_manager(void){
    free(event_mg->events_header);
    free(event_mg);
}

void poll_events(void){
    SDL_Event event;
    reset_array(event_mg->events_header);

    while (SDL_PollEvent(&event)) {
        append(event_mg->events_header, &event);
        event_mg->events_list = Array(event_mg->events_header, SDL_Event); //just in case the array is resized
    }
}
