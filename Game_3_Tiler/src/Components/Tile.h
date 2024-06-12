#pragma once

#include "../Engine/Engine.h"
#include <string>
#include <unordered_map>

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