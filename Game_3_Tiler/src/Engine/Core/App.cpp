#include "App.h"

App::App(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags)
    : _window(Window::Manager(title, x, y, w, h, flags)),
      _renderer(Graphics::Manager(_window.GetRenderer())),
      _assetManager(Asset::Manager(_window.GetRenderer()))
{
    this->AddSystem(System::RENDER, Render::System);
}

App &App::AddPlugin(void (*func)(App *))
{
    func(this);
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)())
{
    _systems[schedule].emplace_back([=] {
        func();
    });
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)(Engine::World &))
{
    _systems[schedule].emplace_back([=] {
        func(_registry);
    });
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)(Engine::World &, Dispatcher &))
{
    _systems[schedule].emplace_back([=] {
        func(_registry, _dispatcher);
    });
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)(Engine::World &, Asset::Manager))
{
    _systems[schedule].emplace_back([=] {
        func(_registry, _assetManager);
    });
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)(Engine::World &, Input::Manager))
{
    _systems[schedule].emplace_back([=] {
        func(_registry, _inputManager);
    });
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)(Engine::World &, Dispatcher &, Input::Manager))
{
    _systems[schedule].emplace_back([=] {
        func(_registry, _dispatcher, _inputManager);
    });
    return *this;
}

App &App::AddSystem(System::Schedule schedule, void (*func)(Engine::World &, Graphics::Manager &renderer))
{
    _systems[schedule].emplace_back([=] {
        func(_registry, _renderer);
    });
    return *this;
}

void App::Run()
{
    for (auto &system: _systems[System::Schedule::SETUP]) {
        system();
    }

    // Add loop for setup
    bool isRunning = true;
    while (isRunning) {
        _window.FrameStart();
        _inputManager.Update();

        _inputManager.ProcessEvents(&isRunning);

        // Loop for update
        for (auto &system: _systems[System::Schedule::UPDATE]) {
            system();
        }

        _dispatcher.Update();

        _renderer.SetDrawColor();
        _window.Clear();

        // loop for render
        for (auto &system: _systems[System::Schedule::RENDER]) {
            system();
        }

        _window.LimitFrameRate();
        _window.Present();
    }
}
