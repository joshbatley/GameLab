#pragma once

#include <unordered_map>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

const std::string SPRITE_TEXTURE_KEY = "spriteMap";

enum Type {
    DEFAULT,
    Water,
    Land
};

class Tile {
public:
    Tile();
    int Size = 16;
    Type type = DEFAULT;
    glm::ivec2 src;
};

std::unordered_map<Type, Tile> setupTileTypes();

