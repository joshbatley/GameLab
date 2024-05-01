#pragma once

#include <SDL_rect.h>
#include <string>

const std::string SPRITE_TEXTURE_KEY = "spriteMap";

class Tile {
public:
    Tile(int x, int y) : destX(x), destY(y) {}
    int destX = 0;
    int destY = 0;

    inline SDL_Rect GetSrcTile() {
        return SDL_Rect {_srcX, _srcY, _size, _size};
    }

    inline SDL_Rect GetDestTile() {
        return SDL_Rect {destX * 32, destY * 32, _size, _size};
    }

private:
    int _srcX = 0;
    int _srcY = 0;
    int _size = 32;
};
