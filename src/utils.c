#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>

#include "consts.h"
#include "utils.h"
#include "parse.h"

void *next_aligned_pointer(void *ptr, size_t alignment){
    return (void *)(((uintptr_t)ptr + (alignment - 1)) & ~(alignment - 1));
}

void print_error(char process_name[]) {
    fprintf(stderr, "Something went wrong with %s D:\n", process_name);
    fprintf(stderr, "%s", SDL_GetError());
}

int initialize_everything() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Something wrong went while  D:\n");
    print_error("initializing everything");
    return 1;
  }
  return 0;
}

int create_window(SDL_Window **window, int flags) {
  *window = SDL_CreateWindow("Test", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
  if (!*window) {
    print_error("creating window");
    return 1;
  }
  return 0;
}

int create_renderer(SDL_Window *window, SDL_Renderer **renderer) {
  *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!*renderer) {
    print_error("creating renderer");
    return 1;
  }
  return 0;
}

void quit(SDL_Window *window, SDL_Renderer *renderer){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

SDL_Surface *copy_surface(SDL_Surface *surface){
    SDL_Surface *copy = SDL_CreateRGBSurfaceWithFormat(0, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->format);
    SDL_BlitSurface(surface, NULL, copy, NULL);
    return copy;
}

SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path){
    SDL_Surface *image = SDL_LoadBMP(path);
    SDL_Texture *texture = NULL;

    if (!image) {
        print_error("loading image");
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, image);

        if (!texture) {
            print_error("loading texture");
        }
    }

    SDL_FreeSurface(image);
    return texture;
}

// Must be a file path with an extension, otherwise will not work
char *get_file_name(char *path){
    size_t splits = times_found(path, "/") + 1;

    char *temp = strdup(path);
    char *token = strtok(temp, "/.");
    while (splits != 2 && token != NULL){
        token = strtok(NULL, "/.");
        splits--;
    }

    char *name = strdup(token);
    free(temp);

    return name;
}

void clear_screen(SDL_Renderer *renderer, SDL_Texture *target, SDL_Color color){
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void render_display(SDL_Renderer *renderer, SDL_Window *window, SDL_Texture *display){
    SDL_SetRenderTarget(renderer, NULL);

    int display_width, display_height, access;
    Uint32 format;
    SDL_QueryTexture(display, &format, &access, &display_width, &display_height);

    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    double scale_x = (double) window_width / (double) display_width;
    double scale_y = (double) window_height / (double) display_height;
    double min_scale = SDL_min(scale_x, scale_y);

    int to_center_x = (window_width - display_width * min_scale) / 2;
    int to_center_y = (window_height - display_height * min_scale) / 2;

    SDL_Rect rect = {to_center_x, to_center_y, display_width * min_scale, display_height * min_scale};

    SDL_RenderCopy(renderer, display, NULL, &rect);
}
