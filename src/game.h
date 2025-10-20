#ifndef TETRIS_H
#define TETRIS_H

#include <SDL2/SDL.h>
#include <stdint.h>

#include "assets.h"
#include "consts.h"
#include "list.h"

#define FIELD_HEIGHT 20
#define FIELD_WIDTH 10
#define TILE_SIZE 8

typedef struct Vec2D {
    int x, y;
} Vec2D;

typedef enum TetrominoID {
    Z = 1,
    S = 2,
    T = 3,
    L = 4,
    O = 5,
    J = 6,
    I = 7,
} TetrominoID;

typedef struct Tetromino {
    uint32_t *rotations;
    Vec2D position; 
    TetrominoID id;
    int current_rotation;
} Tetromino;

extern ArrayHeader *the_sack;
extern ArrayHeader *discarded_tetrominos;

void render_field(SDL_Renderer *renderer, SDL_Texture *target, int field[FIELD_HEIGHT][FIELD_WIDTH]);
size_t decide_tetromino_width(TetrominoID id);
Tetromino create_tertomino(Vec2D position, TetrominoID id);
void init_sack(void);
void restock_the_sack(void);
Tetromino choose_tetromino(void);
int tetromino_timer(size_t level);
void move(Tetromino *tetromino, int field[FIELD_HEIGHT][FIELD_WIDTH]);
void rotate(Tetromino *tetromino, int field[FIELD_HEIGHT][FIELD_WIDTH]);
void fall(Tetromino *tetromino, int field[FIELD_HEIGHT][FIELD_WIDTH]);
void render_tetromino(SDL_Renderer *renderer, Tetromino tetromino);

#endif
