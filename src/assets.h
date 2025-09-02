#ifndef ASSETS_H
#define ASSETS_H

#include <SDL2/SDL.h>
#include "table.h"

/*Singleton*/
typedef struct SpriteManager{
    HashTable *textures;
} SpriteManager;

typedef struct DataManager{
    HashTable *data;
} DataManager;

extern SpriteManager *sprite_mg;
extern DataManager *data_mg;

SpriteManager *init_sprite_manager(unsigned int length);
void destroy_sprite_manager(void);
void sprite_manager_load_texture(SDL_Renderer *renderer, char *path);
SDL_Texture *sprite_manager_get_texture(char *key);
void sprite_manager_delete_texture(char *key);

DataManager *init_data_manager(unsigned int length);
void destroy_data_manager(void);
void load_tetromino_rotations(char *path);
uint32_t *get_tetromino_rotations(char *tetromino);

#endif
