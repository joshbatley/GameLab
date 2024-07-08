#pragma once
#include "Core/WindowManager.h"

class AppSettings {
public:
    static AppSettings &GetInstance()
    {
        static AppSettings instance;
        return instance;
    }

    void SetWindowManager(Window::Manager *windowManager)
    {
        _windowManager = windowManager;
    }

    // Look at moving this to the events on SDL
    std::pair<int, int> WindowSize()
    {
        if (_windowManager == nullptr) {
            throw std::runtime_error("Window Manager not set");
        }

        int width, height;
        SDL_GetWindowSize(_windowManager->GetWindow(), &width, &height);
        return std::make_pair(width, height);
    }


private:
    Window::Manager *_windowManager;
    AppSettings() {}
    ~AppSettings() {}
};
