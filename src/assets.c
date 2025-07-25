#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"
#include "table.h"
#include "parse.h"


SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char *path){
  SDL_Surface *image = SDL_LoadBMP(path);
  SDL_Texture *texture = NULL;

  if (!image) {
    print_error("loading image");
  } else {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

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

void sprite_manager_load_texture(sprite_manager_t *sp_mg, SDL_Renderer *renderer, char *path){
    SDL_Texture *texture = load_bmp_as_texture(renderer, path);
    char *name = file_name(path);

    hash_table_insert(sp_mg->textures_hash_table, name, texture, TEXTURE);
    free(name);
}

SDL_Texture *sprite_manager_get_texture(sprite_manager_t *sp_mg, char *key){
    return hash_table_get(sp_mg->textures_hash_table, key);
}

void sprite_manager_delete_texture(sprite_manager_t *sp_mg, char *key){
    hash_table_delete(sp_mg->textures_hash_table, key);
}

sprite_manager_t *init_sprite_manager(unsigned int length){
    sprite_manager_t *sp_mg = malloc(sizeof(sprite_manager_t));

    if (sp_mg != NULL){
        sp_mg->textures_hash_table = init_hashtable(jenkins_one_at_a_time_hash, length);
    }

    return sp_mg;
}

