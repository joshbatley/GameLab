#include "Renderer.h"

namespace Renderer {
    Manager::Manager(SDL_Renderer *renderer) : renderer(renderer)
    {
        TTF_Init();
    }

    void Manager::CleanUp() const
    {
        for (const auto &pair: fontMap) {
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
        fontMap.insert({key, font});
    }

    void Manager::LoadTexture(std::string key, const char *path)
    {
        SDL_Surface *tmp = IMG_Load(path);
        if (tmp == nullptr) {
            std::cout << "Texture not loaded from path" << path << std::endl;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_FreeSurface(tmp);
        textureMap.insert({key, texture});
    }

    void Manager::RenderText(const char *text, const std::string &key, const SDL_Color color, SDL_Rect &dest)
    {
        const auto font = fontMap[key];
        SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
        if (surface == nullptr) {
            std::cout << "Font not loaded for " << font << std::endl;
        }
        SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
        dest.w = surface->w;
        dest.h = surface->h;
        SDL_RenderCopy(renderer, message, nullptr, &dest);
    }

    void Manager::Render(const std::string &key, const SDL_Rect src, const SDL_Rect dest)
    {
        const auto texture = textureMap[key];
        SDL_RenderCopy(renderer, texture, &src, &dest);
    }

    void Manager::SetDrawColor() const
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}