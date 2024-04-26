#include "WindowManager.h"

namespace Window {
    Manager::Manager(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags)
    {
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

        SDL_ShowCursor(SDL_DISABLE);
    }

    void Manager::Clear() const
    {
        SDL_RenderClear(renderer);
    }

    void Manager::Present() const
    {
        SDL_RenderPresent(renderer);
    }

    void Manager::CleanUp() const
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Manager::FrameStart()
    {
        frameStart = SDL_GetTicks();
    }

    void Manager::LimitFrameRate() const
    {
        const Uint32 frame_end = SDL_GetTicks();
        const Uint32 frame_time = frame_end - frameStart;
        constexpr int frame_delay = 1000 / FRAME_RATE;

        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}// namespace Window