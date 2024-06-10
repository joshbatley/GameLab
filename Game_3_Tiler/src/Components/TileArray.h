#pragma once

#include "../Utils/Tile.h"
#include <array>

namespace TileSize {
    const int multiplier = 2;

    const int Size = 16 * multiplier;
    const int X = 80 / multiplier;
    const int Y = 48 / multiplier;
}

struct TileArray {
    std::array<std::array<Tile *, TileSize::X>, TileSize::Y> Tiles;
};