#include <SDL2/SDL.h>
#include "assets.h"
#include "utils.h"

/*Singleton*/
typedef struct {
    /*SDL_Texture *sprites[];*/
} SpriteManager;

SDL_Texture *load_bmp_as_texture(SDL_Renderer *renderer, char path[]){
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

