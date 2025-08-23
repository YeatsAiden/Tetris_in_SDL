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

extern sprite_manager_t *sprite_mg;
extern data_manager_t *data_mg;

sprite_manager_t *init_sprite_manager(unsigned int length);
void destroy_sprite_manager(void);
void sprite_manager_load_texture(SDL_Renderer *renderer, char *path);
SDL_Texture *sprite_manager_get_texture(char *key);
void sprite_manager_delete_texture(char *key);

data_manager_t *init_data_manager(unsigned int length);
void destroy_data_manager(void);
void load_tetromino(char *path);
uint32_t *get_tetromino_rotations(char *tetromino);

#endif
