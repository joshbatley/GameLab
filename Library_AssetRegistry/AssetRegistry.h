#pragma once

#include "../Alias.h"
#include <SDL_image.h>
#include <iostream>

namespace Asset {
    class Registry {
    public:
        explicit Registry(SDL_Renderer *renderer);
        ~Registry();
        Engine::Font LoadFont(const std::string &key, const char *path, int size);
        Engine::Texture LoadTexture(const std::string &key, const char *path);

    private:
        std::unordered_map<std::string, Engine::Font> _fontMap;
        std::unordered_map<std::string, Engine::Texture> _textureMap;
        SDL_Renderer *_renderer;
    };
}
