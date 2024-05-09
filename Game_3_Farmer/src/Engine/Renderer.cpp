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

    void Manager::RenderText(const char *text, const std::string &key, utils::ivec4 color, utils::ivec4 &dest)
    {
        const auto font = fontMap[key];
        SDL_Color c = { (Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w };
        SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, c);
        if (surface == nullptr) {
            std::cout << "Font not loaded for " << font << std::endl;
        }
        SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect d = { dest.x, dest.y, surface->w, surface->h };
        SDL_RenderCopy(renderer, message, nullptr, &d);
    }

    void Manager::RenderColor(const utils::ivec4 color, const utils::ivec4 dest)
    {
        SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.w);
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderFillRect(renderer, &d);
    }

    void Manager::Render(const std::string &key, const utils::ivec4 src, const utils::ivec4 dest)
    {
        SDL_Rect s = {src.x, src.y, src.z, src.w};
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderCopy(renderer, textureMap[key], &s, &d);
    }

    void Manager::SetDrawColor() const
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
}