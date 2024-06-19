#include "Tile.h"

#include <iostream>

Tile::Tile(std::string sprite_map, std::string coin_tex): _coins_left(0), _coins{}, _level{}
{
    _sprite_map = sprite_map;
    _coin_tex = coin_tex;
    _tile_src.w = _tile_src.h = TILE_SIZE;
    _tile_dest.w = _tile_dest.h = TILE_SIZE;
    _coin_src = {0, 0, TILE_SIZE, TILE_SIZE};
}

void Tile::LoadLevel(const int level)
{
    switch (level) {
        case 1:
            for (int x = 0; x < LEVEL_SIZE; x++) {
                for (int y = 0; y < LEVEL_SIZE; y++) {
                    _level[y][x] = Levels::LEVEL_1[y][x];
                    loadCoins();
                }
            }
            break;
        case 2:
            for (int x = 0; x < LEVEL_SIZE; x++) {
                for (int y = 0; y < LEVEL_SIZE; y++) {
                    _level[y][x] = Levels::LEVEL_2[y][x];
                    loadCoins();
                }
            }
            break;
        case 3:
            for (int x = 0; x < LEVEL_SIZE; x++) {
                for (int y = 0; y < LEVEL_SIZE; y++) {
                    _level[y][x] = Levels::LEVEL_3[y][x];
                    loadCoins();
                }
            }
            break;
        default:
            break;
    }
}

bool Tile::RemoveCoin(const int x, const int y)
{
    if (_coins[x][y] == 1) {
        _coins[x][y] = 0;
        _coins_left--;
    }

    if (_coins_left <= 0) {
        return true;
    }
    return false;
}

int GetNumber(const int x, const int y)
{
    constexpr int seed = 1000;
    srand(x * 10 + y + seed);
    return rand() % 12;
}

std::vector<std::tuple<SDL_Rect, SDL_Rect, std::string>> Tile::Render()
{
    std::vector<std::tuple<SDL_Rect, SDL_Rect, std::string>> toRender;
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            const int type = _level[y][x] - 1;
            _tile_dest.x = x * 32;
            _tile_dest.y = y * 32;
            if (type == 47) {
                _tile_src.x = GetNumber(x, y) * TILE_SIZE;
                _tile_src.y = 4 * TILE_SIZE;
            } else {
                const int posX = type % 12;
                const int posY = type / 12;
                _tile_src.x = posX * TILE_SIZE;
                _tile_src.y = posY * TILE_SIZE;
            }
            toRender.emplace_back(_tile_src, _tile_dest, _sprite_map);
            if (_coins[x][y] == 1) {
                toRender.emplace_back(_coin_src, _tile_dest, _coin_tex);
            }
        }
    }
    return toRender;
}

void Tile::loadCoins()
{
    _coins_left = 0;
    for (int x = 0; x < 15; x++) {
        for (int y = 0; y < 15; y++) {
            if (_level[y][x] == 48) {
                _coins_left++;
                _coins[x][y] = 1;
            } else {
                _coins[x][y] = 0;
            }
        }
    }
}