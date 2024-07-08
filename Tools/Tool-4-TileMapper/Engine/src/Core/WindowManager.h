#pragma once

#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>

namespace Window {
    struct Config {
        const char *title = "Window";
        int width = 1280;
        int height = 768;
        int x = SDL_WINDOWPOS_CENTERED;
        int y = SDL_WINDOWPOS_CENTERED;
        Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
        bool showCursor = false;
        bool relativeMouse = true;
    };

    constexpr int FRAME_RATE = 100;

    class Manager {
    public:
        explicit Manager(const Config &config);
        ~Manager();

        void Clear() const;
        void Present() const;
        void FrameStart();
        void LimitFrameRate() const;
        void ImGuiFrame();
        void ImGuiRender();

        SDL_Renderer *GetRenderer() const
        {
            return _renderer;
        }

        SDL_Window *GetWindow() const
        {
            return +_window;
        }

    private:
        SDL_Renderer *_renderer = nullptr;
        SDL_Window *_window = nullptr;
        Uint32 _frameStart = 0;

        void Initialize(const char *title, int x, int y, int w, int h, Uint32 flags, bool showCursor, bool relativeMouse);
    };
}// namespace Window