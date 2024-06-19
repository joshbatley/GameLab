#include "AssetRegistry.h"

namespace Asset {
    Registry::Registry(SDL_Renderer *renderer)
        : _renderer(renderer)
    {
        TTF_Init();
    }

    Registry::~Registry()
    {
        for (const auto &pair: _fontMap) {
            TTF_CloseFont(pair.second);
        }
    }

    Engine::Font Registry::LoadFont(const std::string &key, const char *path, int size)
    {
        auto *font = TTF_OpenFont(path, size);
        if (font == nullptr) {
            std::cout << "Font not loaded from " << path << std::endl;
        }
        _fontMap.insert({key, font});
        return font;
    }

    Engine::Texture Registry::LoadTexture(const std::string &key, const char *path)
    {
        auto *tmp = IMG_Load(path);
        if (tmp == nullptr) {
            std::cout << "Texture not loaded from path" << path << std::endl;
        }
        auto *texture = SDL_CreateTextureFromSurface(_renderer, tmp);
        SDL_FreeSurface(tmp);
        _textureMap.insert({key, texture});
        return texture;
    }
}
