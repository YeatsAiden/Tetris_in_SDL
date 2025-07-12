#include <SDL2/SDL.h>
#include "consts.h"
#include "utils.h"
#include "assets.h"

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int is_running = 1;

    initialize_everything();
    create_window(&window);
    create_renderer(window, &renderer);

    SDL_Texture *red_block = load_bmp_as_texture(renderer, "./assets/red.bmp");
    SDL_Texture *yellow_block = load_bmp_as_texture(renderer, "./assets/yellow.bmp");
    SDL_Texture *orange_block = load_bmp_as_texture(renderer, "./assets/orange.bmp");
    SDL_Texture *green_block = load_bmp_as_texture(renderer, "./assets/green.bmp");
    SDL_Texture *purple_block = load_bmp_as_texture(renderer, "./assets/purple.bmp");
    SDL_Texture *gray_block = load_bmp_as_texture(renderer, "./assets/gray.bmp");

    int FPS = 120;
    float dt = 1.0/FPS, dt_accumulator = 0;
    int previous_time, current_time;

    int field[FIELD_HEIGHT][FIELD_WIDTH] = {0};

    while(is_running){
        recieve_input(&is_running);

        previous_time = current_time;
        current_time = SDL_GetTicks();
        dt_accumulator += (current_time - previous_time) / 1000.0;

        while(dt_accumulator >= dt){
            dt_accumulator -= dt;
        }


        clear_screen(renderer, BLACK);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

