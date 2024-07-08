#include "App.h"

App::App(const Window::Config &config)
    : _windowManager(config),
      _assetHandler(Asset::Handler(_windowManager.GetRenderer())),
      _graphicsHandler(Graphics::Handler(_windowManager.GetRenderer()))
{
    auto &settings = AppSettings::GetInstance();
    settings.SetWindowManager(&_windowManager);
}

void App::Run()
{
    for (auto &system: _systems[System::Schedule::SETUP]) {
        system();
    }

    bool isRunning = true;
    while (isRunning) {
        _windowManager.FrameStart();
        _inputManager.Update();
        _inputManager.ProcessEvents(&isRunning);

        for (auto &system: _systems[System::Schedule::UPDATE]) {
            system();
        }

        _eventHandler.Update();
        _graphicsHandler.SetDrawColor();
        _windowManager.Clear();

        for (auto &system: _systems[System::Schedule::RENDER]) {
            system();
        }

        _windowManager.LimitFrameRate();
        _windowManager.Present();
    }
}
