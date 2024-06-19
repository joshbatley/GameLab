#pragma once

#include "../Core/Vector.h"
#include "../Engine.h"

struct Sprite {
    Engine::Texture texture {};
    Vec::ivec2 src {};
    Vec::ivec2 size {};
};