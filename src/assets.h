#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include "table.h"

/*Singleton*/
typedef struct sprite_manager{
    hash_table_t *textures_hash_table;
} sprite_manager_t;

SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path);
sprite_manager_t *init_sprite_manager(unsigned int length);
char *file_name(char *path);
void sprite_manager_load_texture(sprite_manager_t *sp_mg, SDL_Renderer *renderer, char *path);
SDL_Texture *sprite_manager_get_texture(sprite_manager_t *sp_mg, char *key);
void sprite_manager_delete_texture(sprite_manager_t *sp_mg, char *key);

#endif
