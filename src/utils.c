#include <stdio.h>
#include <SDL2/SDL.h>
#include "consts.h"
#include "utils.h"

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

int create_window(SDL_Window **window) {
  *window = SDL_CreateWindow("Test", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

void render_field(SDL_Texture *texture, int field[FIELD_HEIGHT][FIELD_WIDTH]){
   for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            switch (field[y][x]) {
                case 0:

                break;
            }
        }
   }
}

void clear_screen(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}
