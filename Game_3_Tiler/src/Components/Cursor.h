#pragma once

#include <string>

const std::string CURSOR_TEXTURE_KEY = "cursorMap";

struct Cursor {
    Engine::ivec2 Pos;
    float Speed = .5;
};