#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "SDL.h"
#include "SDL_image.h"

class Utils
{
  public:
    static SDL_Texture* LoadTex(SDL_Renderer* renderer, const char* path);
};


#endif// GAME_UTILS_H
