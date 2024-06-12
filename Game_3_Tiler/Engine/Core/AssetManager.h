#pragma once

#include "Graphics.h"
#include "Includes.h"

namespace Asset {
    class Manager {
    public:
        explicit Manager(Graphics::Renderer *renderer);
        ~Manager();
        Graphics::Font LoadFont(std::string key, const char *path, int size);
        Graphics::Texture LoadTexture(std::string key, const char *path);

    private:
        std::unordered_map<std::string, Graphics::Font> _fontMap;
        std::unordered_map<std::string, Graphics::Texture> _textureMap;
        Graphics::Renderer *_renderer;
    };
}
