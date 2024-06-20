#pragma once

#include "Core/Engine.h"
#include <SDL_image.h>
#include <iostream>

namespace Asset {
    class Handler {
    public:
        explicit Handler(SDL_Renderer *renderer);
        ~Handler();
        Engine::Font LoadFont(const std::string &key, const char *path, int size);
        Engine::Texture LoadTexture(const std::string &key, const char *path);

    private:
        std::unordered_map<std::string, Engine::Font> _fontMap;
        std::unordered_map<std::string, Engine::Texture> _textureMap;
        SDL_Renderer *_renderer;
    };
}
