#pragma once

#include "../Engine/Vectors.h"

class Position {
public:
    Position(int x, int y) : Dest(x, y) {}
    Engine::ivec2 Dest;
};
