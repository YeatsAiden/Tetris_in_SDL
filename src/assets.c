#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "assets.h"
#include "utils.h"
#include "table.h"

sprite_manager_t *sprite_mg = NULL;

data_manager_t *data_mg = NULL;

sprite_manager_t *init_sprite_manager(unsigned int length){
    sprite_mg = malloc(sizeof(sprite_manager_t));

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

data_manager_t *init_data_manager(unsigned int length){
    data_mg = malloc(sizeof(data_manager_t));

    if (data_mg != NULL){
        data_mg->data = init_hashtable(jenkins_one_at_a_time_hash, length);
    }

    return data_mg;
}

void destroy_data_manager(void){
    free_hash_table(data_mg->data);
}

void load_tetromino(char *path){
    char *name = get_file_name(path);

    FILE *ptr = fopen(path, "r");

    uint32_t *rotations = malloc(4 * sizeof(uint32_t));

    if (rotations == NULL) return;

    uint32_t mask = 0; // I think this is what is supposed to be called :|
    int ch, times = 0;
    while ((ch = fgetc(ptr)) != EOF){
        if (ch == '\n') {
            times++;

            if ((times % 4 == 0) && (times != 0)){
                rotations[(times / 4) - 1] = mask;
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

