#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "list.h"

typedef struct InputManager {
    int numkeys;
    const Uint8 *temp_keyboard_state;
    Uint8 *current_keyboard_state;
    Uint8 *prev_keyboard_state;
} InputManager;

typedef struct KeyboardInput {
    SDL_Scancode scan_code;
    Uint64 time_stamp;
} KeyboardInput;

extern InputManager *input_mg;

InputManager *init_input_manager(void);
void destroy_input_manager(void);
void update_keyboard_state(void);
void update_previous_keyboard_state(void);
int get_key_pressed(SDL_Scancode scan_code);
int get_key_down(SDL_Scancode scan_code);

#endif
