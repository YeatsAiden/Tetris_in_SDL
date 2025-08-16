#include <SDL2/SDL.h>

#include "assets.h"
#include "consts.h"
#include "game.h"

void render_field(SDL_Renderer *renderer, SDL_Texture *target, sprite_manager_t *sp_mg, int field[FIELD_HEIGHT][FIELD_WIDTH]){
    SDL_SetRenderTarget(renderer, target);
    for(int y=0;y<FIELD_HEIGHT;y++){
        for(int x=0;x<FIELD_WIDTH;x++){
            SDL_Rect rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            switch (field[y][x]) {
                case 0:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "gray"), NULL, &rect);
                break;
                case 1:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "red"), NULL, &rect);
                break;
                case 2:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "green"), NULL, &rect);
                break;
                case 3:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "purple"), NULL, &rect);
                break;
                case 4:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "orange"), NULL, &rect);
                break;
                case 5:
                    SDL_RenderCopy(renderer, sprite_manager_get_texture(sp_mg, "yellow"), NULL, &rect);
                break;
            }
        }
   }
}


