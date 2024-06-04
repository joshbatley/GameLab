#pragma once

#include "../Engine/Vectors.h"
#include <string>
#include <unordered_map>

const std::string SPRITE_TEXTURE_KEY = "spriteMap";

enum Type {
    DEFAULT,
    Water,
    Land,
    Sand
};

struct Tile {
    Type type = DEFAULT;
    Engine::ivec2 src;
    int Size = 16;
};

const std::unordered_map<Type, Tile> TileTypes {
  {Type::Water, Tile {Type::Water, {12 * 16, 11 * 16}}},
  {Type::Land, Tile {Type::Land, {0 * 16, 1 * 16}}},
  {Type::Sand, Tile {Type::Sand, {1 * 16, 11 * 16}}}};