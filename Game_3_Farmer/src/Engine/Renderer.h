#pragma once

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>
#include "../Utils/Vectors.h"

namespace Renderer {
    class Manager {
    public:
        Manager(SDL_Renderer *renderer);
        void CleanUp() const;

        void LoadFont(std::string key, const char *path, int size);
        void LoadTexture(std::string key, const char *path);

        void RenderText(const char *text, const std::string &key, utils::ivec4 color, utils::ivec4 &dest);
        void RenderColor(const utils::ivec4 color, const utils::ivec4 dest);
        void Render(const std::string &key, utils::ivec4 src, utils::ivec4 dest);
        void SetDrawColor() const;

    private:
        SDL_Renderer *renderer;
        std::unordered_map<std::string, TTF_Font *> fontMap;
        std::unordered_map<std::string, SDL_Texture *> textureMap;
    };
}