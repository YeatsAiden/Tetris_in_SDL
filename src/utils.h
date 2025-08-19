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

SDL_Surface *copy_surface(SDL_Surface *surface);
SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path);
char *get_file_name(char *path);

void clear_screen(SDL_Renderer *renderer, SDL_Texture *target, SDL_Color color);
void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display);

#endif
