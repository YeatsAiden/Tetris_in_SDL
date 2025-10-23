#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "game.h"
#include "assets.h"
#include "input.h"
#include "list.h"

char *id_to_tetromino[] = { [Z]="Z", [S]="S", [T]="T", [L]="L", [O]="O", [J]="J", [I]="I" }; //By far one of the coolest features C has)
char *tetromino_colors[] = {"gray", [Z]="red", [S]="green", [T]="purple", [L]="orange", [O]="yellow", [J]="dark_blue", [I]="light_blue" };

int JLSTZ_tests[4][5][2] = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0 ,-2}, {-1, -2}},
};

int I_tests[4][5][2] = {
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},
    {{-1, 0}, {0, 0}, {0, 0}, {0, -1}, {0, 2}},
    {{-1, -1}, {1, -1}, {-2, -1}, {1, 0}, {-2, 0}},
    {{0, -1}, {0, -1}, {0, -1}, {0, 1}, {0, -2}},
};

int O_tests[4][5][2] = {
    {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},},
    {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1},},
    {{-1, 1}, {-1, 1}, {-1, 1}, {-1, 1}, {-1, 1},},
    {{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},},
};

ArrayHeader *the_sack = NULL;
ArrayHeader *discarded_tetrominos = NULL;

void draw_square(SDL_Renderer *renderer, SDL_Rect *rect, int id) {
    SDL_RenderCopy(renderer, sprite_manager_get_texture(tetromino_colors[id]), NULL, rect);
}

void render_field(SDL_Renderer *renderer, SDL_Texture *target, int field[FIELD_HEIGHT][FIELD_WIDTH]) {
    SDL_SetRenderTarget(renderer, target);
    for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            draw_square(renderer, &rect, field[y][x]);
        }
   }
}

size_t decide_tetromino_width(TetrominoID id) {
    return id == I ? 5 : 3;
}

Tetromino create_tertomino(Vec2D position, TetrominoID id) {
    return (Tetromino) {
        .position = position,
        .rotations = get_tetromino_rotations(id_to_tetromino[id]),
        .id = id,
        .current_rotation = 0,
    };
}

void init_sack(void){
    if (the_sack == NULL) {
        the_sack = Init_Array_Header(&the_sack, TetrominoID, 7);

        for (int i=0;i<the_sack->length;i++) {
            TetrominoID id = (rand() % the_sack->length) + 1;
            while (includes(the_sack, &id) != -1) id = (rand() % the_sack->length) + 1;

            append(the_sack, &id);
        }
    }

    if (discarded_tetrominos == NULL) {
        discarded_tetrominos = Init_Array_Header(&discarded_tetrominos, TetrominoID, 7);
    }
}

void restock_the_sack(void) {
    int index = rand() % discarded_tetrominos->count;

    TetrominoID *discarded_tetrominos_array = Array(discarded_tetrominos, TetrominoID);
    TetrominoID chosen_tetromino_id = discarded_tetrominos_array[index];

    while(discarded_tetrominos->count != 0){
        append(the_sack, &chosen_tetromino_id);
        pop(discarded_tetrominos, index);

        index = rand() % discarded_tetrominos->count;
        chosen_tetromino_id = discarded_tetrominos_array[index];
    }
}

Tetromino choose_tetromino(void) {
    int index = rand() % the_sack->count;

    TetrominoID *the_sack_array = Array(the_sack, TetrominoID);
    TetrominoID chosen_tetromino_id = the_sack_array[index];

    append(discarded_tetrominos, &chosen_tetromino_id);
    pop(the_sack, index);

    Tetromino tetromino = create_tertomino((Vec2D) {.x = 3, .y = 0}, chosen_tetromino_id);
    return tetromino;
}

int tetromino_timer(size_t level) {
    static Uint32 current_time = 0;
    static Uint32 previous_time = 0;

    current_time = SDL_GetTicks();

    if ((double)(current_time - previous_time) / 1000 >= pow(0.8 - ((level-1)*0.007), level-1)) {
        previous_time = current_time;
        return 1;
    } else {
        return 0;
    }
}

int check_position(Tetromino *tetromino, Vec2D offset, int field[FIELD_HEIGHT][FIELD_WIDTH]) {
    size_t width = decide_tetromino_width(tetromino->id);

    Vec2D new_pos = {
        .x = tetromino->position.x + offset.x,
        .y = tetromino->position.y + offset.y,
    };

    for (int y=0;y<width;y++) {
        for (int x=0;x<width;x++) {
            int tetromino_bit = (tetromino->rotations[tetromino->current_rotation] >> ((width - y - 1) * width + (width - x - 1))) & 0b1;
            if ((new_pos.y + y > FIELD_HEIGHT - 1 && tetromino_bit) || (((new_pos.x + x > FIELD_WIDTH - 1) || (new_pos.x + x < 0)) && tetromino_bit)) return 0;
            int field_bit = field[new_pos.y + y][new_pos.x + x];
            if (field_bit != 0 && tetromino_bit == 1) return 0;
        }
    }

    return 1;
}

void move(Tetromino *tetromino, int field[FIELD_HEIGHT][FIELD_WIDTH]) {
    int x_velocity = 0;

    if (get_key_pressed(SDL_SCANCODE_RIGHT)) x_velocity += 1;
    if (get_key_pressed(SDL_SCANCODE_LEFT)) x_velocity -= 1;

    if (check_position(tetromino, (Vec2D) { .x = x_velocity, .y = 0 }, field)){
        tetromino->position.x += x_velocity;
    };
}

void fall(Tetromino *tetromino, int field[FIELD_HEIGHT][FIELD_WIDTH]) {
    if (check_position(tetromino, (Vec2D) { .x = 0, .y = 1 }, field)){
        tetromino->position.y += 1;
    };
}

int *decide_tetromino_tests(TetrominoID id) {
        switch (id) {
        case I:
            return (int *)I_tests;
        break;
        case O:
            return (int *)O_tests;
        break;
        default:
            return (int *)JLSTZ_tests;
    }
}

void rotate(Tetromino *tetromino, int field[FIELD_HEIGHT][FIELD_WIDTH]) {
    int rotation_direction = get_key_pressed(SDL_SCANCODE_UP) - get_key_pressed(SDL_SCANCODE_DOWN);

    if (!rotation_direction) return;

    int new_rotation = (tetromino->current_rotation + rotation_direction) % 4;

    if (new_rotation < 0) new_rotation = 4 + new_rotation;

    int offsets[5][2] = {0};

    int tests[5][4][2] = {0};
    memcpy(tests, decide_tetromino_tests(tetromino->id), 5 * 4 * 2); // OOOOHHH MaGiC NUmbERsS

    for (int i=0;i<5;i++) {
        offsets[i][0] = tests[tetromino->current_rotation][i][0] - tests[new_rotation][i][0];
        offsets[i][1] = tests[tetromino->current_rotation][i][1] - tests[new_rotation][i][1];
    }

    tetromino->current_rotation = new_rotation;

    for (int i=0;i<5;i++) {
        if (check_position(tetromino, (Vec2D) { .x = offsets[i][0], .y = offsets[i][1] }, field)) {
            tetromino->position.x += offsets[i][0];
            tetromino->position.y += offsets[i][1];
            break;
        }
    }
}

void render_tetromino(SDL_Renderer *renderer, Tetromino tetromino) {
    size_t width = decide_tetromino_width(tetromino.id);

    for (int y=0;y<width;y++){
        for (int x=0;x<width;x++){
            int tetromino_bit = (tetromino.rotations[tetromino.current_rotation] >> ((width - y - 1) * width + (width - x - 1))) & 0b1;
            if (tetromino_bit == 1){
                SDL_Rect rect = {
                    .x = (tetromino.position.x + x) * TILE_SIZE,
                    .y = (tetromino.position.y + y) * TILE_SIZE,
                    .w = TILE_SIZE,
                    .h = TILE_SIZE,
                };

                draw_square(renderer, &rect, tetromino.id);
            }
        }
    }
}
