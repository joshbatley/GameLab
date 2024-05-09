#pragma once

#include <unordered_map>
#include <string>
#include "../Utils/Vectors.h"

const std::string SPRITE_TEXTURE_KEY = "spriteMap";

enum Type {
    DEFAULT,
    Water,
    Land,
    Sand
};

class Tile {
public:
    Tile();
    int Size = 16;
    Type type = DEFAULT;
    utils::ivec2 src;
};

std::unordered_map<Type, Tile> setupTileTypes();
