#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "assets.h"
#include "utils.h"
#include "table.h"

SpriteManager *sprite_mg = NULL;

DataManager *data_mg = NULL;

SpriteManager *init_sprite_manager(unsigned int length){
    sprite_mg = malloc(sizeof(SpriteManager));

    if (sprite_mg != NULL){
        sprite_mg->textures = init_hashtable(jenkins_one_at_a_time_hash, length);
    }

    return sprite_mg;
}

void destroy_sprite_manager(void){
    free_hash_table(sprite_mg->textures);
}

void sprite_manager_load_texture(SDL_Renderer *renderer, char *path){
    SDL_Texture *texture = load_bmp_as_texture(renderer, path);
    char *name = get_file_name(path);

    hash_table_insert(sprite_mg->textures, name, texture, TEXTURE);
    free(name);
}

SDL_Texture *sprite_manager_get_texture(char *key){
    return hash_table_get(sprite_mg->textures, key);
}

void sprite_manager_delete_texture(char *key){
    hash_table_delete(sprite_mg->textures, key);
}

DataManager *init_data_manager(unsigned int length){
    data_mg = malloc(sizeof(DataManager));

    if (data_mg != NULL){
        data_mg->data = init_hashtable(jenkins_one_at_a_time_hash, length);
    }

    return data_mg;
}

void destroy_data_manager(void){
    free_hash_table(data_mg->data);
}

void load_tetromino_rotations(char *path){
    char *name = get_file_name(path);

    FILE *ptr = fopen(path, "r");

    uint64_t *rotations = malloc(4 * sizeof(uint64_t));

    if (rotations == NULL) return;

    uint64_t mask = 0; // I think this is what is supposed to be called :|
    int ch, times = 0;

    size_t width = memcmp(name, "I", 1) == 0 ? 5 : 3;

    while ((ch = fgetc(ptr)) != EOF){
        if (ch == '\n') {
            times++;

            if ((times % width == 0) && (times != 0)){
                rotations[(times / width) - 1] = mask;
                mask = 0;
            }

            continue;
        }
        mask = mask << 1 | (ch - '0');
    }

    fclose(ptr);

    hash_table_insert(data_mg->data, name, rotations, OTHER);

    free(name);
}

uint32_t *get_tetromino_rotations(char *tetromino){
    return (uint32_t *)hash_table_get(data_mg->data, tetromino);
}

