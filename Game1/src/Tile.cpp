#include "Tile.h"
#include <cstdlib>
#include <iostream>

Tile::Tile(SDL_Renderer* renderer)
{
    sprite_sheet = Utils::LoadTex(renderer, path.c_str());
    coin = Utils::LoadTex(renderer, count_path.c_str());
    src.w = src.h = 32;
    dest.w = dest.h = 32;
    LoadCoins();
}

Tile::~Tile()
{}

int GetNumber(int x, int y)
{
    int seed = 1000;
    srand(x * 10 + y + seed);
    return rand() % 12;
}

void Tile::render(SDL_Renderer* renderer)
{
    for (int row = 0; row < 15; row++) {
        for (int col = 0; col < 15; col++) {
            int type = Level->at(row).at(col) - 1;
            dest.x = col * 32;
            dest.y = row * 32;
            if (type == 47) {
                src.x = GetNumber(row, col) * tileSize;
                src.y = 4 * tileSize;
            } else {
                int x = type % 12;
                int y = type / 12;
                src.x = x * tileSize;
                src.y = y * tileSize;
            }
            SDL_RenderCopy(renderer, sprite_sheet, &src, &dest);
            if (coins[row][col] == 1) {
                SDL_RenderCopy(renderer, coin, &coin_src, &dest);
            }
        }
    }
}

void Tile::loadLevel(int lvl)
{
    switch (lvl) {
    case 1:
        Level = &level1;
        LoadCoins();
        break;
    case 2:
        Level = &level2;
        LoadCoins();
        break;
    case 3:
        Level = &level3;
        LoadCoins();
        break;
    }
}

void Tile::LoadCoins()
{
    coins_left = 0;
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            if (Level->at(x).at(y) == 48) {
                coins_left++;
                coins[x][y] = 1;
            } else {
                coins[x][y] = 0;
            }
        }
    }
}
bool Tile::removeCoin(int x, int y)
{
    if (coins[x][y] == 1) {
        coins[x][y] = 0;
        coins_left--;
    }

    if (coins_left <= 0) {
        return true;
    }
    return false;

    //    for (int x = 0; x < 15; x++) {
    //        for (int y = 0; y < 15; y++) {
    //            if (coins[x][y] == 1) {
    //
    //            }
    //        }
    //    }
}
