#pragma once

#include "SDL.h"
#include <iostream>

namespace Window {
    constexpr int FRAME_RATE = 60;

    class Manager {
    public:
        Manager(const char *title, int x, int y, int w, int h, Uint32 flags);
        void Clear() const;
        void Present() const;
        void CleanUp() const;
        void FrameStart();
        void LimitFrameRate() const;

        SDL_Renderer *GetRenderer() const
        {
            return renderer;
        }

    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        Uint32 frameStart = 0;
    };
}