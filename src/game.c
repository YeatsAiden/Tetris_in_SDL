#include <SDL2/SDL.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "assets.h"
#include "consts.h"
#include "list.h"
#include "game.h"

char *id_to_tetromino[] = { [Z]="Z", [S]="S", [T]="T", [L]="L", [O]="O", [J]="J", [I]="I"}; //By far one of the coolest features C has)

int JLSTZ_tests[4][5][2] = {
    {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0 ,-2}, {-1, -2}},
};

int I_tests[4][5][2] = {
    {{0, 0}, {2, 0}, {-1, 0}, {2, -1}, {-1, 2}},
    {{0, 0}, {-2, 0}, {1, 0}, {-2, 1}, {1, -2}},
    {{0, 0}, {1, 0}, {-2, 0}, {1, 2}, {-2, -1}},
    {{0, 0}, {-1, 0}, {2, 0}, {-1, -2}, {2, 1}},
};

array_header_t *the_sack = NULL;
array_header_t *discarded_tetrominos = NULL;

void render_field(SDL_Renderer *renderer, SDL_Texture *target, int field[FIELD_HEIGHT][FIELD_WIDTH]){
    SDL_SetRenderTarget(renderer, target);
    for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            switch (field[y][x]) {
                case 0:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("gray"), NULL, &rect);
                break;
                case Z:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("red"), NULL, &rect);
                break;
                case S:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("green"), NULL, &rect);
                break;
                case T:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("purple"), NULL, &rect);
                break;
                case L:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("orange"), NULL, &rect);
                break;
                case O:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("yellow"), NULL, &rect);
                break;
                case J:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("dark_blue"), NULL, &rect);
                break;
                case I:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture("light_blue"), NULL, &rect);
                break;
            }
        }
   }
}

tetromino_t create_tertomino(point_t position, Tetromino_Id_t id){
    return (tetromino_t) {
        .position = position,
        .rotations = get_tetromino_rotations(id_to_tetromino[id]),
        .id = id,
    };
}

void init_sack(void){
    if (the_sack == NULL) {
        the_sack = Init_Array_Header(&the_sack, Tetromino_Id_t, 7);

        for (int i=0;i<7;i++) {
            Tetromino_Id_t id = (rand() % 7) + 1;
            while (includes(the_sack, &id)) id = (rand() % 7) + 1;

            append(the_sack, &id);
        }
    }

    if (discarded_tetrominos == NULL) {
        discarded_tetrominos = Init_Array_Header(&discarded_tetrominos, Tetromino_Id_t, 7);
    }
}

void restock_the_sack(void){
    int index = rand() % discarded_tetrominos->count;

    Tetromino_Id_t *discarded_tetrominos_array = Array(discarded_tetrominos, Tetromino_Id_t);
    Tetromino_Id_t chosen_tetromino_id = discarded_tetrominos_array[index];

    while(discarded_tetrominos->count != 0){
        append(the_sack, &chosen_tetromino_id);
        pop(discarded_tetrominos, index);

        index = rand() % discarded_tetrominos->count;
        chosen_tetromino_id = discarded_tetrominos_array[index];
    }
}

tetromino_t choose_tetromino(void){
    int index = rand() % the_sack->count;

    Tetromino_Id_t *the_sack_array = Array(the_sack, Tetromino_Id_t);
    Tetromino_Id_t chosen_tetromino_id = the_sack_array[index];

    append(discarded_tetrominos, &chosen_tetromino_id);
    pop(the_sack, index);

    tetromino_t tetromino = create_tertomino((point_t) {.x = 3, .y = 0}, chosen_tetromino_id);
    return tetromino;
}

int can_tetromino_move(size_t level){
    static Uint32 current_time = 0;
    static Uint32 previous_time = 0;

    previous_time = current_time;
    current_time = SDL_GetTicks();

    return (current_time - previous_time >= pow(0.8 - ((level-1)*0.007), level-1)) ? 1 : 0;
}


