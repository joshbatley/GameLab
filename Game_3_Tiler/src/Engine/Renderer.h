#pragma once

#include "./Vectors.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>

namespace Renderer {
    class Manager {
    public:
        Manager(SDL_Renderer *renderer);
        void CleanUp() const;

        void LoadFont(std::string key, const char *path, int size);
        void LoadTexture(std::string key, const char *path);

        void RenderText(const char *text, const std::string &key, Engine::ivec4 color, Engine::ivec4 &dest);
        void RenderColor(const Engine::ivec4 color, const Engine::ivec4 dest);
        void Render(const std::string &key, Engine::ivec4 src, Engine::ivec4 dest);
        void SetDrawColor() const;

    private:
        SDL_Renderer *_renderer;
        std::unordered_map<std::string, TTF_Font *> _fontMap;
        std::unordered_map<std::string, SDL_Texture *> _textureMap;
    };
}