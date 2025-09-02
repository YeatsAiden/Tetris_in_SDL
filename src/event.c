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
    event_mg->inputs = Init_Array_Header(&event_mg->events_header, Inputs, 32);

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

void recieve_input(void){
    InputEvent input_event = {0};
    SDL_Event event = {0};

    for (int i=0;i<event_mg->events_header->count;i++) {
        event = event_mg->events_list[i];
        switch (event.type) {
            case SDL_QUIT:
                input_event.input = INPUT_QUIT;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: 
                        input_event.input = INPUT_QUIT;
                        break;
                    case SDLK_RIGHT:
                        input_event.input = INPUT_RIGHT;
                        break;
                    case SDLK_UP:
                        input_event.input = INPUT_UP;
                        break;
                    case SDLK_DOWN:
                        input_event.input = INPUT_DOWN;
                        break;
                    case SDLK_LEFT:
                        input_event.input = INPUT_LEFT;
                        break;
                    case SDLK_z:
                        input_event.input = INPUT_Z_KEY;
                        break;
                    case SDLK_x:
                        input_event.input = INPUT_X_KEY;
                        break;
                }
            break;
        }

        if (input_event.input != 0) {
            input_event.time_stamp = SDL_GetPerformanceCounter();
            append(event_mg->inputs, &input_event);
        }
    }
}

InputEvent check_input(Input input_id){
    
}
