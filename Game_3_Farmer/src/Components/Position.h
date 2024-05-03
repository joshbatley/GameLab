#pragma once

#include "../Utils/Vectors.h"

class Position {
public:
    Position(int x, int y) : Dest(x, y) {}
    utils::ivec2 Dest;
};
