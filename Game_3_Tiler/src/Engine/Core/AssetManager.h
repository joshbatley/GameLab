#pragma once

#include "../Alias.h"
#include <SDL_image.h>

namespace Asset {
    class Manager {
    public:
        explicit Manager(SDL_Renderer *renderer);
        ~Manager();
        Engine::Font LoadFont(const std::string &key, const char *path, int size);
        Engine::Texture LoadTexture(const std::string &key, const char *path);

    private:
        std::unordered_map<std::string, Engine::Font> _fontMap;
        std::unordered_map<std::string, Engine::Texture> _textureMap;
        SDL_Renderer *_renderer;
    };
}
