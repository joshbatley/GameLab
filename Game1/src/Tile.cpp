
#include "Tile.h"
#include <cstdlib>
#include <iostream>

Tile::Tile(SDL_Renderer* renderer)
{
    sprite_sheet = Utils::LoadTex(renderer, path.c_str());
    src.w = src.h = 32;
    dest.w = dest.h = 32;
}

Tile::~Tile()
{}

const int tileSize = 32;

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
            switch (type) {
            case 47:
                src.x = GetNumber(row, col) * tileSize;
                src.y = 4 * tileSize;
                break;
            default:
                int x = type % 12;
                int y = type / 12;
                src.x = x * tileSize;
                src.y = y * tileSize;
            }
            SDL_RenderCopy(renderer, sprite_sheet, &src, &dest);
        }
    }
}
void Tile::loadLevel(int lvl)
{
    switch (lvl) {
    case 1:
        Level = &level1;
        break;
    case 2:
        Level = &level2;
        break;
    case 3:
        Level = &level3;
        break;
    }
}
