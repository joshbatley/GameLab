#include "GraphicsHandler.h"

namespace Graphics {
    Handler::Handler(SDL_Renderer *renderer)
        : _renderer(renderer) {}

    void Handler::RenderText(const char *text, Engine::Font font, Vec::ivec4 color, Vec::ivec4 &dest)
    {
        SDL_Color c = {(Uint8)color.x, (Uint8)color.y, (Uint8)color.z, (Uint8)color.w};
        auto *surface = TTF_RenderUTF8_Solid(font, text, c);
        if (surface == nullptr) {
            std::cout << "Font not loaded for " << font << std::endl;
        }
        auto *message = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_Rect d = {dest.x, dest.y, surface->w, surface->h};
        SDL_RenderCopy(_renderer, message, nullptr, &d);
    }

    void Handler::RenderColor(Vec::ivec4 color, const Vec::ivec4 dest)
    {
        SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderFillRect(_renderer, &d);
    }

    void Handler::Render(Engine::Texture texture, Vec::ivec4 src, const Vec::ivec4 dest)
    {
        SDL_Rect s = {src.x, src.y, src.z, src.w};
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderCopy(_renderer, texture, &s, &d);
    }

    void Handler::SetDrawColor()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }
}