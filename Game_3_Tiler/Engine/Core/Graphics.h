#pragma once

#include "Includes.h"
#include "Vectors.h"
#include <iostream>
#include <unordered_map>

namespace Graphics {
    using Texture = SDL_Texture *;
    using Font = TTF_Font *;
    using Renderer = SDL_Renderer;

    class Manager {
    public:
        explicit Manager(Graphics::Renderer *renderer);
        void RenderText(const char *text, Graphics::Font font, Vec::ivec4 color, Vec::ivec4 &dest);
        void RenderColor(Vec::ivec4 color, Vec::ivec4 dest);
        void Render(Graphics::Texture texture, Vec::ivec4 src, Vec::ivec4 dest);
        void SetDrawColor() const;

    private:
        Graphics::Renderer *_renderer;
    };
}