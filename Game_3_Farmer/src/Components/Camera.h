#pragma once

#include "../Utils/Vectors.h"

struct Camera {
    int scale = 8;
    int speed = 1;
    utils::ivec2 pos = { 0, 0 };
};