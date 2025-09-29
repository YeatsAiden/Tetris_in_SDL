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

InputManager *init_input_manager(void);
void input_check(void);

#endif
