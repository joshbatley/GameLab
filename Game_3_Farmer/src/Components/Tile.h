#pragma once

#include <unordered_map>
#include <string>
#include "../Engine/Vectors.h"

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
    Engine::ivec2 src;
    Engine::color color = {0,0,0,0};
};

std::unordered_map<Type, Tile> setupTileTypes();
