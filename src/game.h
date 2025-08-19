#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <stdint.h>

#include "assets.h"
#include "consts.h"

typedef struct point {
    int x, y;
} point_t;

typedef enum Tetromino_Id {
    Z = 1,
    S = 2,
    T = 3,
    L = 4,
    O = 5,
    J = 6,
    I = 7,
} Tetromino_Id_t;

typedef struct tetromino {
    uint32_t *rotations;
    point_t position; 
    size_t width;
    Tetromino_Id_t id;
} tetromino_t;

typedef struct piece_manager {
    hash_table_t *pieces;
} piece_manager_t;

void render_field(SDL_Renderer *renderer, SDL_Texture *target, int field[FIELD_HEIGHT][FIELD_WIDTH]);

#endif
