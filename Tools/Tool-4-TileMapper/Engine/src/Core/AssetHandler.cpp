#include "AssetHandler.h"

namespace Asset {
    Handler::Handler(SDL_Renderer *renderer)
        : _renderer(renderer)
    {
        TTF_Init();
    }

    Handler::~Handler()
    {
        for (const auto &font: _fontMap) {
            TTF_CloseFont(font);
        }
    }

    Engine::Font Handler::LoadFont(const char *path, int size)
    {
        auto *font = TTF_OpenFont(path, size);
        if (font == nullptr) {
            std::cout << "Font not loaded from " << path << std::endl;
        }
        _fontMap.emplace_back(font);
        return font;
    }

    Engine::Texture Handler::LoadTexture(const char *path)
    {
        auto *tmp = IMG_Load(path);
        if (tmp == nullptr) {
            std::cout << "Texture not loaded from path" << path << std::endl;
        }
        auto *texture = SDL_CreateTextureFromSurface(_renderer, tmp);
        SDL_FreeSurface(tmp);
        return texture;
    }
}
