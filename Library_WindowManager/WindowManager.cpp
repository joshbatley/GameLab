#include "WindowManager.h"

WindowManager::WindowManager(const char *title, int x, int y, int w, int h, Uint32 flags) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cout << "SDL failed to init. Error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window == nullptr) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
        return;
    }

    TTF_Init();
}

void WindowManager::Clear() {
    SDL_RenderClear(renderer);
}

void WindowManager::Present() {
    SDL_RenderPresent(renderer);
}

void WindowManager::CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    for (const auto& pair : fonts) {
        TTF_CloseFont(pair.second);
    }
    TTF_Quit();
}

void WindowManager::FrameStart() {
    frameStart = SDL_GetTicks();
}

void WindowManager::LimitFrameRate() const {
    Uint32 frame_end = SDL_GetTicks();
    Uint32 frame_time = frame_end - frameStart;
    int frame_delay = 1000 / FRAME_RATE;

    if (frame_time < frame_delay) {
        SDL_Delay(frame_delay - frame_time);
    }
}

void WindowManager::LoadFont(const char* name, const char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);
    fonts.insert({name, font});
}

SDL_Texture* WindowManager::LoadTexture(const char* path) {
    SDL_Surface* tmp = IMG_Load(path);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    return tex;
}

void WindowManager::RenderText(const char *text, const char *fontKey, SDL_Color color, SDL_Rect dest) {
    auto font = fonts[fontKey];
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, message, NULL, &dest);
}

void WindowManager::Render(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(renderer, texture, &src, &dest);
}