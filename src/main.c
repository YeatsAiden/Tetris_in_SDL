#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include "consts.h"
#include "utils.h"
#include "assets.h"

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int is_running = 1;

    initialize_everything();
    create_window(&window, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    create_renderer(window, &renderer);

    SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, DISPLAY_WIDTH, DISPLAY_HEIGHT);

    sprite_manager_t *sp_mg = init_sprite_manager(10);
    sprite_manager_load_texture(sp_mg, renderer,  "./assets/red.bmp");
    sprite_manager_load_texture(sp_mg, renderer,  "./assets/yellow.bmp");
    sprite_manager_load_texture(sp_mg, renderer,  "./assets/orange.bmp");
    sprite_manager_load_texture(sp_mg, renderer,  "./assets/green.bmp");
    sprite_manager_load_texture(sp_mg, renderer,  "./assets/purple.bmp");
    sprite_manager_load_texture(sp_mg, renderer,  "./assets/gray.bmp");

    int FPS = 120;
    double dt = 1.0/FPS, dt_accumulator = 0;
    unsigned int previous_time = 0, current_time = 0;

    int field[FIELD_HEIGHT][FIELD_WIDTH] = {0};

    while(is_running){
        recieve_input(&is_running);

        current_time = SDL_GetPerformanceCounter();
        dt_accumulator += (current_time - previous_time) / (float) SDL_GetPerformanceFrequency();
        previous_time = current_time;

        while(dt_accumulator >= dt){
            dt_accumulator -= dt;
        }

        clear_screen(renderer, NULL, BLACK);
        render_field(renderer, display, sp_mg, field);
        render_display(renderer, window, display);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}

