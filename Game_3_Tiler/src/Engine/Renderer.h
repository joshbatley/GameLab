#pragma once

#include "./Vectors.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>

using Texture = SDL_Texture *;
using Font = TTF_Font *;

namespace Renderer {
    class Manager {
    public:
        explicit Manager(SDL_Renderer *renderer);
        void RenderText(const char *text, Font font, Engine::ivec4 color, Engine::ivec4 &dest);
        void RenderColor(Engine::ivec4 color, Engine::ivec4 dest);
        void Render(Texture texture, Engine::ivec4 src, Engine::ivec4 dest);
        void SetDrawColor() const;

    private:
        SDL_Renderer *_renderer;
    };
}