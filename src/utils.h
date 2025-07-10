#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include "consts.h"

void print_error(char process[]);
int initialize_everything();
int create_window(SDL_Window **window);
int create_renderer(SDL_Window *window, SDL_Renderer **renderer);
void recieve_input(int *is_running);
void render_field(SDL_Texture *texture, int field[FIELD_HEIGHT][FIELD_WIDTH]);
void clear_screen(SDL_Renderer *renderer, SDL_Color color);

#endif
