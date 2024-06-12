#pragma once

#include <SDL.h>
#include <iostream>

namespace Window {
    constexpr int FRAME_RATE = 100;

    class Manager {
    public:
        Manager(const char *title, int x, int y, int w, int h, Uint32 flags);
        ~Manager();

        void Clear() const;
        void Present() const;
        void FrameStart();
        void LimitFrameRate() const;

        SDL_Renderer *GetRenderer() const
        {
            return _renderer;
        }

    private:
        SDL_Renderer *_renderer;
        SDL_Window *_window;
        Uint32 _frameStart = 0;
    };
}