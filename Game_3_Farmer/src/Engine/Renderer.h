#pragma once

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <iostream>
#include <unordered_map>
#include "../Components/Components.h"

namespace Renderer {
    class Manager {
    public:
        Manager(SDL_Renderer *renderer);
        void CleanUp() const;

        void LoadFont(std::string key, const char *path, int size);
        void LoadTexture(std::string key, const char *path);

        void RenderText(const char *text, const std::string &key, SDL_Color color, SDL_Rect &dest);
        void RenderColor(const SDL_Color color, const SDL_Rect dest);
        void Render(const std::string &key, SDL_Rect src, SDL_Rect dest);
        void SetDrawColor() const;

    private:
        SDL_Renderer *renderer;
        std::unordered_map<std::string, TTF_Font *> fontMap;
        std::unordered_map<std::string, SDL_Texture *> textureMap;
    };
}