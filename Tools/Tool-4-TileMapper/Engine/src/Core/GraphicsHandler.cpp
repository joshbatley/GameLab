#include "GraphicsHandler.h"

#include <glm/vec2.hpp>

namespace Graphics {
    Handler::Handler(SDL_Renderer *renderer)
        : _renderer(renderer) {}

    void Handler::RenderText(const char *text, Engine::Font font, glm::ivec4 color, glm::ivec4 &dest)
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

    void Handler::Render(Engine::Texture texture, glm::ivec4 src, const glm::ivec4 dest)
    {
        SDL_Rect s = {src.x, src.y, src.z, src.w};
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderCopy(_renderer, texture, &s, &d);
    }

    void Handler::DrawLine(glm::ivec4 color, glm::ivec2 start, glm::ivec2 end)
    {
        SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
        SDL_RenderDrawLine(_renderer, start.x, start.y, end.x, end.y);
    }

    void Handler::DrawRect(glm::ivec4 color, glm::ivec4 rect)
    {
        SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
        SDL_Rect d = {rect.x, rect.y, rect.z, rect.w};
        SDL_RenderDrawRect(_renderer, &d);
    }

    void Handler::DrawRectFill(glm::ivec4 color, glm::ivec4 dest)
    {
        SDL_SetRenderDrawColor(_renderer, color.x, color.y, color.z, color.w);
        SDL_Rect d = {dest.x, dest.y, dest.z, dest.w};
        SDL_RenderFillRect(_renderer, &d);
    }

    void Handler::SetDrawColor()
    {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    }
}// namespace Graphics