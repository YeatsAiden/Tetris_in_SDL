#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include "consts.h"
#include "assets.h"

void *next_aligned_pointer(void *ptr, size_t alignment);
void print_error(char process[]);
int initialize_everything();
int create_window(SDL_Window **window, int flags);
int create_renderer(SDL_Window *window, SDL_Renderer **renderer);
void recieve_input(int *is_running);
void clear_screen(SDL_Renderer *renderer, SDL_Texture *target, SDL_Color color);
void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display);

#endif
