#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <stdint.h>
#include <stdlib.h>

#include "event.h"
#include "list.h"

event_manager_t *event_mg = NULL;

event_manager_t *init_event_manager(void){
    event_mg = malloc(sizeof(event_manager_t));

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

uint16_t recieve_input(){
    uint16_t inputs = 0;

    for (int i=0;i<event_mg->events_header->count;i++) {
        SDL_Event event = event_mg->events_list[i];

        switch (event.type) {

            case SDL_QUIT:
                inputs = inputs | (1 << 7);
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {

                    case SDLK_ESCAPE: 
                        inputs = inputs | (1 << 7);
                        break;

                    case SDLK_RIGHT:
                        inputs = inputs | 1;
                        break;

                    case SDLK_UP:
                        inputs = inputs | (1 << 1);
                        break;

                    case SDLK_DOWN:
                        inputs = inputs | (1 << 2);
                        break;

                    case SDLK_LEFT:
                        inputs = inputs | (1 << 3);
                        break;

                    case SDLK_z:
                        inputs = inputs | (1 << 4);
                        break;

                    case SDLK_x:
                        inputs = inputs | (1 << 5);
                        break;
                }
                break;
        }
    }

    return inputs;
}

