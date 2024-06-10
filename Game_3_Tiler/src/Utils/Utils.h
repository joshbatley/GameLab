#pragma once

#include "Noise.h"
#include "Tile.h"

template<typename T>
T lerp(T a, T b, float t)
{
    return a + (b - a) * t;
}