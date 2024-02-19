
#include "Tile.h"
#include <cstdlib>

Tile::Tile(SDL_Renderer* renderer)
{
    sprite_sheet = Utils::LoadTex(renderer, path.c_str());
    src.w = src.h = 32;
    dest.w = dest.h = 32;
}

Tile::~Tile()
{}

const int tileSize = 32;

// 15, 15 // 12
int GetNumber(int x, int y)
{
    int seed = 1000;// Example seed value
    srand(x * 10 + y + seed);
    return rand() % 12;
}

void Tile::render(SDL_Renderer* renderer)
{
    for (int row = 0; row < 15; row++) {
        for (int col = 0; col < 15; col++) {
            int type = Level->at(row).at(col);
            dest.x = col * 32;
            dest.y = row * 32;
            switch (type) {
            case 0:
                src.y = 4 * tileSize;
                src.x = GetNumber(row, col) * tileSize;
                break;
            case 1:
                src.y = 2 * tileSize;
                src.x = 1 * tileSize;
                break;
            case 2:
                src.y = 0 * tileSize;
                src.x = 1 * tileSize;
                break;
            case 3:
                src.y = 1 * tileSize;
                src.x = 2 * tileSize;
                break;
            case 4:
                src.y = 1 * tileSize;
                src.x = 0 * tileSize;
                break;
            case 5:
                src.y = 2 * tileSize;
                src.x = 8 * tileSize;
                ;
                break;
            case 6:
                src.y = 2 * tileSize;
                src.x = 9 * tileSize;
                break;
            case 7:
                src.y = 2 * tileSize;
                src.x = 10 * tileSize;
                break;
            case 8:
                src.y = 2 * tileSize;
                src.x = 11 * tileSize;
                break;
            case 9:
                src.y = 0 * tileSize;
                src.x = 0 * tileSize;
                break;
            case 10:
                src.y = 0 * tileSize;
                src.x = 2 * tileSize;
                break;
            case 11:
                src.y = 2 * tileSize;
                src.x = 0 * tileSize;
                break;
            case 12:
                src.y = 2 * tileSize;
                src.x = 2 * tileSize;
                break;
            case 13:
                src.y = 1 * tileSize;
                src.x = 1 * tileSize;
                break;
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
    }
}
