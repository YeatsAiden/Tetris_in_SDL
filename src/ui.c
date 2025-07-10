#include <SDL2/SDL.h>

typedef struct {
  SDL_Texture *image;
  SDL_Rect rect;
  int clicked;
} Button;

Button button_from_texture(int x, int y, SDL_Texture *texture) {
    int width, height, access;
    unsigned int format;
    SDL_QueryTexture(texture, &format, &access, &width, &height);
    return (Button){texture, (SDL_Rect){x, y, width, height}, 0};
}
