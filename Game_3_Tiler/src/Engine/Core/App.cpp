#include "App.h"

App::App(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags, bool showCursor, bool relativeMouse)
    : _window(Window::Manager(title, x, y, w, h, flags, showCursor, relativeMouse)),
      _renderer(Graphics::Manager(_window.GetRenderer())),
      _assetManager(Asset::Manager(_window.GetRenderer()))
{
    this->AddSystem(System::RENDER, Render::System);
}

App::App(Window::Config config)
    : _window(config),
      _renderer(Graphics::Manager(_window.GetRenderer())),
      _assetManager(Asset::Manager(_window.GetRenderer()))
{
    this->AddSystem(System::RENDER, Render::System);
}

void App::Run()
{
    for (auto &system: _systems[System::Schedule::SETUP]) {
        system();
    }

    bool isRunning = true;
    while (isRunning) {
        _window.FrameStart();
        _inputManager.Update();

        _inputManager.ProcessEvents(&isRunning);

        for (auto &system: _systems[System::Schedule::UPDATE]) {
            system();
        }

        _dispatcher.Update();

        _renderer.SetDrawColor();
        _window.Clear();

        for (auto &system: _systems[System::Schedule::RENDER]) {
            system();
        }

        _window.LimitFrameRate();
        _window.Present();
    }
}
