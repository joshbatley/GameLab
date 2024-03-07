#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <unordered_map>
#include <iostream>

const int FRAME_RATE = 60;

class WindowManager {
public:
    WindowManager(const char *title, int x, int y, int w, int h, Uint32 flags);
    void Clear();
    void Present();
    void CleanUp();
    void FrameStart();
    void LimitFrameRate() const;

    void LoadFont(const char* name, const char* path, int size);
    SDL_Texture* LoadTexture(const char* path);

    void RenderText(const char *text, const char *fontKey, SDL_Color color, SDL_Rect dest);
    void Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    Uint32 frameStart = 0;
    std::unordered_map<const char*, TTF_Font*> fonts;
};

#endif//WINDOW_H
