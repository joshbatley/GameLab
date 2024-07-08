#include "WindowManager.h"

namespace Window {
    Manager::Manager(const Config &config)
    {
        Initialize(config.title, config.x, config.y, config.width, config.height, config.flags, config.showCursor, config.relativeMouse);
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

        ImGui::CreateContext();
        auto &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
        ImGui_ImplSDLRenderer2_Init(_renderer);
    }

    Manager::~Manager()
    {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

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
        auto &io = ImGui::GetIO();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), _renderer);
        SDL_RenderSetScale(_renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
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

    void Manager::ImGuiFrame()
    {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void Manager::ImGuiRender()
    {
        ImGui::Render();
    }
}// namespace Window