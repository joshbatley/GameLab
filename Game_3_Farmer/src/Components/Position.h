#pragma once

#include <glm/vec2.hpp>

class Position {
public:
    Position(int x, int y) : Dest(x, y) {}
    glm::ivec2 Dest;
};
