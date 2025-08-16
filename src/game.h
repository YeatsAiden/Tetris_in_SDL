#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <stdint.h>

#include "list.h"
#include "assets.h"
#include "consts.h"

// O, I, J, L, T, S, Z
/*      
    O = 0000    --->    0000 0110 0110 0000
        0110    ( by iterating in rows I get a 16 bit array and save it as a uint32_t)
        0110
        0000

    I = 0000    0010    0000    0100
        1111    0010    0000    0100
        0000    0010    1111    0100
        0000    0010    0000    0100

    J = 1000    0110    0000    0100
        1110    0100    1110    0100
        0000    0100    0010    1100
        0000    0000    0000    0000

    L = 0010    0100    0000    1100
        1110    0100    1110    0100
        0000    0110    1000    0100
        0000    0000    0000    0000

    T = 0100    0100    0000    0100
        1110    0110    1110    1100
        0000    0100    0100    0100
        0000    0000    0000    0000

    S = 0110    0100    0000    1000
        1100    0110    0110    1100
        0000    0010    1100    0100
        0000    0000    0000    0000

    Z = 1100    0010    0000    0100
        0110    0110    1100    1100
        0000    0100    0110    1000
        0000    0000    0000    0000
*/

typedef struct tetromino {
    uint32_t rotations[4];
} tetromino_t;

typedef struct piece_manager {
    hash_table_t *pieces;
} piece_manager_t;

void render_field(SDL_Renderer *renderer, SDL_Texture *target, sprite_manager_t *sp_mg, int field[FIELD_HEIGHT][FIELD_WIDTH]);

#endif
