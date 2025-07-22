#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include "table.h"

/*Singleton*/
typedef struct sprite_manager{
    hash_table_t *textures_hash_table;
    void (*load_texture)(struct sprite_manager *sp_mg, SDL_Renderer *renderer, char *path);
    SDL_Texture* (*get_texture)(struct sprite_manager *sp_mg, char *key);
    void (*delete_texture)(struct sprite_manager *sp_mg, char *key);
} sprite_manager_t;

SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path);
sprite_manager_t *init_sprite_manager(unsigned int length);

#endif
