#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assets.h"
#include "utils.h"
#include "table.h"
#include "parse.h"

sprite_manager_t *sp_mg = NULL;

data_manager_t *dt_mg = NULL;

SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path){
    SDL_Surface *image = SDL_LoadBMP(path);
    SDL_Texture *texture = NULL;

    if (!image) {
        print_error("loading image");
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, image);

        if (!texture) {
            print_error("loading texture");
        }
    }

    SDL_FreeSurface(image);
    return texture;
}

char *file_name(char *path){
    size_t splits = times_found(path, "/") + 1;

    char *temp = strdup(path);
    char *token = strtok(temp, "/.");
    while (splits != 2 && token != NULL){
        token = strtok(NULL, "/.");
        splits--;
    }

    char *name = strdup(token);
    free(temp);

    return name;
}

void sprite_manager_load_texture(SDL_Renderer *renderer, char *path){
    SDL_Texture *texture = load_bmp_as_texture(renderer, path);
    char *name = file_name(path);

    hash_table_insert(sp_mg->textures, name, texture, TEXTURE);
    free(name);
}

SDL_Texture *sprite_manager_get_texture(char *key){
    return hash_table_get(sp_mg->textures, key);
}

void sprite_manager_delete_texture(char *key){
    hash_table_delete(sp_mg->textures, key);
}

sprite_manager_t *init_sprite_manager(unsigned int length){
    sp_mg = malloc(sizeof(sprite_manager_t));

    if (sp_mg != NULL){
        sp_mg->textures = init_hashtable(jenkins_one_at_a_time_hash, length);
    }

    return sp_mg;
}

void load_tetromino(char *path){
    char *name = file_name(path);

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

    hash_table_insert(dt_mg->data, name, rotations, OTHER);

    free(name);
}

uint32_t *get_tetromino(char *key){
    return (uint32_t *)hash_table_get(dt_mg->data, key);
}

data_manager_t *init_data_manager(unsigned int length){
    dt_mg = malloc(sizeof(data_manager_t));

    if (dt_mg != NULL){
        dt_mg->data = init_hashtable(jenkins_one_at_a_time_hash, length);
    }

    return dt_mg;
}
