#pragma once

#include "Core/Engine.h"
#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <iostream>

namespace Graphics {
    class Handler {
    public:
        explicit Handler(SDL_Renderer *renderer);
        void RenderText(const char *text, Engine::Font font, glm::ivec4 color, glm::ivec4 &dest);
        void Render(Engine::Texture texture, glm::ivec4 src, glm::ivec4 dest);
        void SetDrawColor();

        void DrawLine(glm::ivec4 color, glm::ivec2 start, glm::ivec2 end);
        void DrawRect(glm::ivec4 color, glm::ivec4 rect);
        void DrawRectFill(glm::ivec4 color, glm::ivec4 dest);

    private:
        SDL_Renderer *_renderer;
    };
}// namespace Graphics