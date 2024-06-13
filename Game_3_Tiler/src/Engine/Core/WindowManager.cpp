#include "WindowManager.h"

namespace Window {
    Manager::Manager(Config config)
    {
        Initialize(config.title, config.x, config.y, config.width, config.height, config.flags, config.showCursor, config.relativeMouse);
    }

    Manager::Manager(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags, bool showCursor, bool relativeMouse)
    {
        Initialize(title, x, y, w, h, flags, showCursor, relativeMouse);
    }

    void Manager::Initialize(const char *title, int x, int y, int w, int h, Uint32 flags, bool showCursor, bool relativeMouse)
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
            std::cout << "SDL failed to init. Error: " << SDL_GetError() << std::endl;
            return;
        }

        _window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (_window == nullptr) {
            std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
            return;
        }

        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (_renderer == nullptr) {
            std::cout << "Graphics failed to init. Error: " << SDL_GetError() << std::endl;
            return;
        }

        if (showCursor) {
            SDL_ShowCursor(SDL_DISABLE);
        }
        if (relativeMouse) {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }

    Manager::~Manager()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
    }

    void Manager::Clear() const
    {
        SDL_RenderClear(_renderer);
    }

    void Manager::Present() const
    {
        SDL_RenderPresent(_renderer);
    }

    void Manager::FrameStart()
    {
        _frameStart = SDL_GetTicks();
    }

    void Manager::LimitFrameRate() const
    {
        const auto frame_end = SDL_GetTicks();
        const auto frame_time = frame_end - _frameStart;
        constexpr int frame_delay = 1000 / FRAME_RATE;

        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }
    }
}