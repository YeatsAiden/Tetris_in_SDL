#include <SDL2/SDL.h>
#include <stdint.h>

#include "consts.h"
#include "utils.h"
#include "assets.h"
#include "input.h"
#include "game.h"

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    initialize_everything();
    create_window(&window, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    create_renderer(window, &renderer);

    SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    init_input_manager();

    init_data_manager(7);
    load_tetromino("./assets/data/T.txt");
    load_tetromino("./assets/data/O.txt");
    load_tetromino("./assets/data/L.txt");
    load_tetromino("./assets/data/J.txt");
    load_tetromino("./assets/data/Z.txt");
    load_tetromino("./assets/data/S.txt");
    load_tetromino("./assets/data/I.txt");

    init_sprite_manager(10);
    sprite_manager_load_texture(renderer,  "./assets/images/red.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/yellow.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/orange.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/green.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/purple.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/gray.bmp");

    int FPS = 120;
    double dt = 1.0/FPS, dt_accumulator = 0;
    unsigned int previous_time = 0, current_time = 0;
    uint8_t flags = 0;

    int field[FIELD_HEIGHT][FIELD_WIDTH] = {0};

    while(~flags & 1){
        flags = poll_events();

        current_time = SDL_GetPerformanceCounter();
        dt_accumulator += (current_time - previous_time) / (float) SDL_GetPerformanceFrequency();
        previous_time = current_time;

        while(dt_accumulator >= dt){
            dt_accumulator -= dt;
        }

        clear_screen(renderer, NULL, BLACK);
        render_field(renderer, display, field);
        render_display(renderer, window, display);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

