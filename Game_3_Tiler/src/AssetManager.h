#pragma once

#include "Engine/Engine.h"

namespace Asset {
    class Manager {
    public:
        explicit Manager(SDL_Renderer *renderer);
        ~Manager();
        Font LoadFont(std::string key, const char *path, int size);
        Texture LoadTexture(std::string key, const char *path);

    private:
        std::unordered_map<std::string, Font> _fontMap;
        std::unordered_map<std::string, Texture> _textureMap;
        SDL_Renderer *_renderer;
    };
}
