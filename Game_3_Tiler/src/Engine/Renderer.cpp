#include "Renderer.h"

namespace Renderer {
    Manager::Manager(SDL_Renderer *renderer)
        : _renderer(renderer)
    {
        TTF_Init();
    }

    void Manager::CleanUp() const
    {
        for (const auto &pair: _fontMap) {
            TTF_CloseFont(pair.second);
        }
        TTF_Quit();
    }

    void Manager::LoadFont(std::string key, const char *path, const int size)
    {
        TTF_Font *font = TTF_OpenFont(path, size);
        if (font == nullptr) {
            std::cout << "Font not loaded from " << path << std::endl;
        }
        _fontMap.insert({key, font});
    }

    void Manager::LoadTexture(std::string key, const char *path)
    {
        SDL_Surface *tmp = IMG_Load(path);
        if (tmp == nullptr) {
            std::cout << "Texture not loaded from path" << path << std::endl;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, tmp);
        SDL_FreeSurface(tmp);
        _textureMap.insert({key, texture});
    }

    void Manager::RenderText(const char *text, const std::string &key, Engine::ivec4 color, Engine::ivec4 &dest)
    {
        const auto font = _fontMap[key];
        SDL_Color c = {(Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w};
        SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, c);
        if (surface == nullptr) {
            std::cout << "Font not loaded for " << font << std::endl;
        }
        SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_Rect d = {dest.x, dest.y, surface->w, surface->h};
        SDL_RenderCopy(_renderer, message, nullptr, &d);
    }

    void Manager::RenderColor(const Engine::ivec4 color, const Engine::ivec4 dest)
    {
        SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderFillRect(_renderer, &d);
    }

    void Manager::Render(const std::string &key, const Engine::ivec4 src, const Engine::ivec4 dest)
    {
        SDL_Rect s = {src.x, src.y, src.z, src.w};
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderCopy(_renderer, _textureMap[key], &s, &d);
    }

    void Manager::SetDrawColor() const
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }
}