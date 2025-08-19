#include <SDL2/SDL.h>

#include "assets.h"
#include "consts.h"
#include "game.h"

char *id_to_tetromino[] = { [Z]="Z", [S]="S", [T]="T", [L]="L", [O]="O", [J]="J", [I]="I"};

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
        .rotations = get_tetromino(id_to_tetromino[id]),
        .width = 4,
        .id = id,
    };
}
