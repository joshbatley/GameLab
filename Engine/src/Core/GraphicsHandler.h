#pragma once

#include "Core/Engine.h"
#include "Core/Vector.h"
#include <SDL.h>
#include <iostream>

namespace Graphics {
    class Handler {
    public:
        explicit Handler(SDL_Renderer *renderer);
        void RenderText(const char *text, Engine::Font font, Vec::ivec4 color, Vec::ivec4 &dest);
        void RenderColor(Vec::ivec4 color, Vec::ivec4 dest);
        void Render(Engine::Texture texture, Vec::ivec4 src, Vec::ivec4 dest);
        void SetDrawColor();

    private:
        SDL_Renderer *_renderer;
    };
}