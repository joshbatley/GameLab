#include "App.h"

App::App(Window::Config config)
    : _window(config),
      _graphics(Graphics::Handler(_window.GetRenderer())),
      _assetRegistry(Asset::Handler(_window.GetRenderer()))
{
    this->AddSystem(System::RENDER, RenderSystem::System);
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

        _eventRegistry.Update();

        _graphics.SetDrawColor();
        _window.Clear();

        for (auto &system: _systems[System::Schedule::RENDER]) {
            system();
        }

        _window.LimitFrameRate();
        _window.Present();
    }
}
