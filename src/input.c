#include <SDL2/SDL.h>
#include "input.h"
#include <stdlib.h>

InputManager *input_mg = NULL;

InputManager *init_input_manager(void) {
    input_mg = malloc(sizeof(InputManager));

    if (input_mg == NULL) return NULL;

    input_mg->temp_keyboard_state = SDL_GetKeyboardState(&input_mg->numkeys);
    input_mg->current_keyboard_state = calloc(input_mg->numkeys, sizeof(Uint8));
    input_mg->prev_keyboard_state = calloc(input_mg->numkeys, sizeof(Uint8));

    return input_mg;
}

void update_keyboard_state(void) {
    input_mg->temp_keyboard_state = SDL_GetKeyboardState(&input_mg->numkeys);
}

void input_check(void) {
}
