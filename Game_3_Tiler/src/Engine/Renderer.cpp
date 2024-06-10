#include "Renderer.h"

namespace Renderer {
    Manager::Manager(SDL_Renderer *renderer)
        : _renderer(renderer) {}

    void Manager::RenderText(const char *text, Font font, Engine::ivec4 color, Engine::ivec4 &dest)
    {
        SDL_Color c = {(Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w};
        SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, c);
        if (surface == nullptr) {
            std::cout << "Font not loaded for " << font << std::endl;
        }
        SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_Rect d = {dest.x, dest.y, surface->w, surface->h};
        SDL_RenderCopy(_renderer, message, nullptr, &d);
    }

    void Manager::RenderColor(Engine::ivec4 color, const Engine::ivec4 dest)
    {
        SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderFillRect(_renderer, &d);
    }

    void Manager::Render(Texture texture, Engine::ivec4 src, const Engine::ivec4 dest)
    {
        SDL_Rect s = {src.x, src.y, src.z, src.w};
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderCopy(_renderer, texture, &s, &d);
    }

    void Manager::SetDrawColor() const
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }
}