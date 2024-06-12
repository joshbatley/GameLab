#include "AssetManager.h"

namespace Asset {
    Manager::Manager(Graphics::Renderer *renderer)
        : _renderer(renderer)
    {
        TTF_Init();
    }

    Manager::~Manager()
    {
        for (const auto &pair: _fontMap) {
            TTF_CloseFont(pair.second);
        }
    }

    Graphics::Font Manager::LoadFont(std::string key, const char *path, int size)
    {
        TTF_Font *font = TTF_OpenFont(path, size);
        if (font == nullptr) {
            std::cout << "Font not loaded from " << path << std::endl;
        }
        _fontMap.insert({key, font});
        return font;
    }

    Graphics::Texture Manager::LoadTexture(std::string key, const char *path)
    {
        SDL_Surface *tmp = IMG_Load(path);
        if (tmp == nullptr) {
            std::cout << "Texture not loaded from path" << path << std::endl;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, tmp);
        SDL_FreeSurface(tmp);
        _textureMap.insert({key, texture});
        return texture;
    }
}
