#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "consts.h"
#include "input.h"
#include "utils.h"
#include "assets.h"
#include "event.h"
#include "input.h"
#include "game.h"

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    srand(time(NULL));

    initialize_everything();
    create_window(&window, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    create_renderer(window, &renderer);

    SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    init_event_manager();
    init_input_manager();

    init_data_manager(7);
    load_tetromino_rotations("./assets/data/T.txt");
    load_tetromino_rotations("./assets/data/O.txt");
    load_tetromino_rotations("./assets/data/L.txt");
    load_tetromino_rotations("./assets/data/J.txt");
    load_tetromino_rotations("./assets/data/Z.txt");
    load_tetromino_rotations("./assets/data/S.txt");
    load_tetromino_rotations("./assets/data/I.txt");

    init_sprite_manager(8);
    sprite_manager_load_texture(renderer,  "./assets/images/red.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/yellow.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/orange.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/green.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/purple.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/gray.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/dark_blue.bmp");
    sprite_manager_load_texture(renderer,  "./assets/images/light_blue.bmp");

    int FPS = 120;
    double dt = 1.0/FPS, dt_accumulator = 0;
    Uint64 previous_time = 0, current_time = 0;

    init_sack(); 
    int field[FIELD_HEIGHT][FIELD_WIDTH] = {0};
    Tetromino current_tetromino = choose_tetromino();
    size_t level = 10, lines_cleared = 0;

    while(!event_mg->quit){
        poll_events();
        update_keyboard_state();

        current_time = SDL_GetPerformanceCounter();
        dt_accumulator += (current_time - previous_time) / (float) SDL_GetPerformanceFrequency();
        previous_time = current_time;

        while(dt_accumulator >= dt){
            if (the_sack->count <= 3) restock_the_sack();

            move(&current_tetromino, field);
            rotate(&current_tetromino, field);

            if (tetromino_timer(level)){
                fall(&current_tetromino, field);
            }

            dt_accumulator -= dt;

            update_previous_keyboard_state();
        }

        clear_screen(renderer, NULL, BLACK);
        render_field(renderer, display, field);
        render_tetromino(renderer, current_tetromino);

        render_display(renderer, window, display);
        SDL_RenderPresent(renderer);
    }

    destroy_sprite_manager();
    destroy_data_manager();
    destroy_event_manager();
    destroy_input_manager();
    quit(window, renderer);

    return 0;
}

