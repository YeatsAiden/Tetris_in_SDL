#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include "table.h"

/*Singleton*/
typedef struct sprite_manager{
    hash_table_t *textures;
} sprite_manager_t;

typedef struct data_manager{
    hash_table_t *data;
} data_manager_t;

extern sprite_manager_t *sp_mg;
extern data_manager_t *dt_mg;

SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path);
char *file_name(char *path);

sprite_manager_t *init_sprite_manager(unsigned int length);
void sprite_manager_load_texture(SDL_Renderer *renderer, char *path);
SDL_Texture *sprite_manager_get_texture(char *key);
void sprite_manager_delete_texture(char *key);

data_manager_t *init_data_manager(unsigned int length);
void load_tetromino(char *path);

#endif
