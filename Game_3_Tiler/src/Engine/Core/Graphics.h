#pragma once

#include "../Alias.h"
#include "Vectors.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>

namespace Graphics {
    class Manager {
    public:
        explicit Manager(SDL_Renderer *renderer);
        void RenderText(const char *text, Engine::Font font, Vec::ivec4 color, Vec::ivec4 &dest);
        void RenderColor(Vec::ivec4 color, Vec::ivec4 dest);
        void Render(Engine::Texture texture, Vec::ivec4 src, Vec::ivec4 dest);
        void SetDrawColor() const;

    private:
        SDL_Renderer *_renderer;
    };
}