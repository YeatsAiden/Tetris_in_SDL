#include <SDL2/SDL.h>
#include "input.h"
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

InputManager *input_mg = NULL;

InputManager *init_input_manager(void) {
    input_mg = malloc(sizeof(InputManager));

    if (input_mg == NULL) return NULL;

    input_mg->temp_keyboard_state = SDL_GetKeyboardState(&input_mg->numkeys);
    input_mg->current_keyboard_state = calloc(input_mg->numkeys, sizeof(Uint8));
    input_mg->prev_keyboard_state = calloc(input_mg->numkeys, sizeof(Uint8));

    return input_mg;
}

void destroy_input_manager(void) {
    free(input_mg->current_keyboard_state);
    free(input_mg->prev_keyboard_state);
    free(input_mg);
}

void update_keyboard_state(void) {
    input_mg->temp_keyboard_state = SDL_GetKeyboardState(&input_mg->numkeys);

    for (int i=0;i<input_mg->numkeys;i++) {
        input_mg->current_keyboard_state[i] |= input_mg->temp_keyboard_state[i];
    }
}

void update_previous_keyboard_state(void) {
    memcpy(input_mg->prev_keyboard_state, input_mg->current_keyboard_state, input_mg->numkeys);
}

int get_key_down(SDL_Scancode scan_code) {
    return input_mg->current_keyboard_state[scan_code];
}

int get_key_pressed(SDL_Scancode scan_code) {
    return !input_mg->prev_keyboard_state[scan_code] && input_mg->current_keyboard_state[scan_code];
}
