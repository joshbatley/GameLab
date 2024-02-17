#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "SDL.h"
#include "Utils.h"
#include <string>

class Player
{
    ~Player();

  public:
    Player(SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
    void Update();

  private:
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* texture;
    std::string path = std::string(SPROUT_LANDS) + "/characters/character-sprites.png";
};


#endif// GAME_PLAYER_H
