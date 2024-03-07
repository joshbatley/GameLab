#include "Utils.h"

SDL_Texture* Utils::LoadTex(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* tmp = IMG_Load(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    return tex;
}
