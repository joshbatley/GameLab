#pragma once

#include "../Alias.h"
#include "../Core/Vector.h"

struct Sprite {
    Engine::Texture texture {};
    Vec::ivec2 src {};
    Vec::ivec2 size {};
};