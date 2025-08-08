#include <SDL2/SDL.h>
#include <stdio.h>
#include "consts.h"
#include "utils.h"
#include "assets.h"

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


void recieve_input(int *is_running) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
        case SDL_QUIT:
          *is_running = 0;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE)
            *is_running = 0;
          break;
    }
  }
}

void render_field(SDL_Renderer *renderer, SDL_Texture *target, sprite_manager_t *sp_mg, int field[FIELD_HEIGHT][FIELD_WIDTH]){
    SDL_SetRenderTarget(renderer, target);
    for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            switch (field[y][x]) {
                case 0:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "gray"), NULL, &rect);
                break;
                case 1:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "red"), NULL, &rect);
                break;
                case 2:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "green"), NULL, &rect);
                break;
                case 3:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "purple"), NULL, &rect);
                break;
                case 4:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "orange"), NULL, &rect);
                break;
                case 5:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "yellow"), NULL, &rect);
                break;
            }
        }
   }
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
