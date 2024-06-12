#pragma once

#include "Engine.h"
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
    float data;
};

const std::unordered_map<Type, Vec::ivec2> TileTypes {
  {Type::Water, {12 * 16, 11 * 16}},
  {Type::Land, {0 * 16, 1 * 16}},
  {Type::Sand, {1 * 16, 11 * 16}}};