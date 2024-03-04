#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "SDL.h"
#include "Utils.h"
#include <string>

class Player
{

  public:
    Player(SDL_Renderer* renderer, int start);
    ~Player();
    void Render(SDL_Renderer* renderer);
    void Update();
    std::pair<int, int> MoveRight(std::vector<std::vector<int>>* level);
    std::pair<int, int> MoveLeft(std::vector<std::vector<int>>* level);
    std::pair<int, int> MoveUp(std::vector<std::vector<int>>* level);
    std::pair<int, int> MoveDown(std::vector<std::vector<int>>* level);

  private:
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* textureDown;
    SDL_Texture* textureUp;
    SDL_Texture* textureLeft;
    SDL_Texture* textureRight;
    SDL_Texture* texture;
    std::string pathDown = std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-front.png";
    std::string pathUp = std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-back.png";
    std::string pathLeft = std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-left.png";
    std::string pathRight = std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-right.png";
};


#endif// GAME_PLAYER_H
