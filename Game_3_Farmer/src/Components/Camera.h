#pragma once

#include "../Engine/Vectors.h"

struct Camera {
    int scale = 8;
    int speed = 1;
    Engine::ivec2 pos = { 0, 0 };
};