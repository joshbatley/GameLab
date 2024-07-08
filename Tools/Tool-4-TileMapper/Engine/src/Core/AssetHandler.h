#pragma once

#include "Core/Engine.h"
#include <SDL_image.h>
#include <iostream>
#include <vector>

namespace Asset {
    class Handler {
    public:
        explicit Handler(SDL_Renderer *renderer);
        ~Handler();
        Engine::Font LoadFont(const char *path, int size);
        Engine::Texture LoadTexture(const char *path);

    private:
        std::vector<Engine::Font> _fontMap;
        SDL_Renderer *_renderer;
    };
}
