#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <stdint.h>

#include "assets.h"
#include "consts.h"
#include "list.h"

typedef struct point {
    int x, y;
} point_t;

typedef enum Tetromino_Id {
    Z = 1,
    S = 2,
    T = 3, L = 4,
    O = 5,
    J = 6,
    I = 7,
} Tetromino_Id_t;

typedef struct tetromino {
    uint32_t *rotations;
    point_t position; 
    Tetromino_Id_t id;
} tetromino_t;

extern array_header_t *the_sack;
extern array_header_t *discarded_tetrominos;

void render_field(SDL_Renderer *renderer, SDL_Texture *target, int field[FIELD_HEIGHT][FIELD_WIDTH]);
tetromino_t create_tertomino(point_t position, Tetromino_Id_t id);
void init_sack(void);
void restock_the_sack(void);
tetromino_t choose_tetromino(void);
int can_tetromino_move(size_t level);

#endif
