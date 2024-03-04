#ifndef GAME_TILE_H
#define GAME_TILE_H

#include "SDL.h"
#include "Utils.h"
#include <string>

const int tileSize = 32;

class Tile
{
  public:
    Tile(SDL_Renderer* renderer);
    ~Tile();
    void render(SDL_Renderer* renderer);
    std::vector<std::vector<int>>* Level = &level1;
    void loadLevel(int lvl);
    bool removeCoin(int x, int y);
    int GetCoinsLeft()
    {
        return coins_left;
    }

  private:
    int coins_left;
    SDL_Rect src;
    SDL_Rect dest;
    SDL_Texture* sprite_sheet;
    SDL_Texture* coin;
    SDL_Rect coin_src = { h : tileSize, w : tileSize, x : 0, y : 0 };
    std::string path = std::string(DUNGEON_STUFF) + "/tiles/dungeon-tiles.png";
    std::string count_path = std::string(DUNGEON_STUFF) + "/objects/coins.png";
    int coins[15][15];
    void LoadCoins();
    std::vector<std::vector<int>> level1 = { { 33, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 34 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 35, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 36 } };

    std::vector<std::vector<int>> level2 = { { 33, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 34 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 1, 3, 48, 48, 48, 48, 48, 48, 48, 1, 3, 48, 13 },
        { 15, 48, 25, 27, 48, 48, 48, 48, 48, 48, 48, 25, 27, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 1, 2, 3, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 13, 14, 15, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 25, 26, 27, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 1, 3, 48, 48, 48, 48, 48, 48, 48, 1, 3, 48, 13 },
        { 15, 48, 25, 27, 48, 48, 48, 48, 48, 48, 48, 25, 27, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 35, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 36 } };

    std::vector<std::vector<int>> level3 = { { 33, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 34 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 1, 2, 2, 2, 2, 2, 3, 48, 8, 48, 8, 48, 13 },
        { 15, 48, 13, 33, 26, 26, 26, 26, 27, 48, 20, 48, 20, 48, 13 },
        { 15, 48, 13, 15, 48, 48, 48, 48, 48, 48, 20, 48, 20, 48, 13 },
        { 15, 48, 13, 15, 48, 4, 5, 5, 5, 5, 31, 5, 29, 48, 13 },
        { 15, 48, 13, 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 25, 30, 05, 5, 5, 5, 5, 5, 5, 5, 6, 48, 13 },
        { 15, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 13 },
        { 15, 48, 4, 6, 48, 16, 5, 5, 5, 5, 5, 5, 17, 48, 13 },
        { 15, 48, 48, 48, 48, 20, 48, 48, 48, 48, 48, 48, 20, 48, 13 },
        { 15, 48, 8, 48, 48, 32, 48, 1, 2, 2, 3, 48, 20, 48, 13 },
        { 15, 48, 28, 6, 48, 48, 48, 25, 26, 26, 27, 48, 20, 48, 13 },
        { 15, 48, 48, 48, 48, 8, 48, 48, 48, 48, 48, 48, 20, 48, 13 },
        { 35, 2, 2, 2, 2, 39, 2, 2, 2, 2, 2, 2, 39, 2, 36 } };
};


#endif// GAME_TILE_H