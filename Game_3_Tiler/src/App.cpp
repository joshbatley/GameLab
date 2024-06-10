#include "App.h"

App::App(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags)
    : _window(Window::Manager(title, x, y, w, h, flags)),
      _renderer(Renderer::Manager(_window.GetRenderer())),
      _assetServer(Asset::Manager(_window.GetRenderer()))
{}

App &App::AddPlugin(void (*func)(App *))
{
    func(this);
    return *this;
}

App &App::AddSystem(Schedule schedule, void (*func)())
{
    _systems[schedule].push_back([=] {
        func();
    });
    return *this;
}

App &App::AddSystem(Schedule schedule, void (*func)(entt::registry &))
{
    _systems[schedule].push_back([=] {
        func(_registry);
    });
    return *this;
}

App &App::AddSystem(Schedule schedule, void (*func)(entt::registry &, Asset::Manager))
{
    _systems[schedule].push_back([=] {
        func(_registry, _assetServer);
    });
    return *this;
}

App &App::AddSystem(Schedule schedule, void (*func)(entt::registry &, Asset::Manager, Input::Manager))
{
    _systems[schedule].push_back([=] {
        func(_registry, _assetServer, _inputManager);
    });
    return *this;
}

App &App::AddSystem(Schedule schedule, void (*func)(entt::registry &, Input::Manager))
{
    _systems[schedule].push_back([=] {
        func(_registry, _inputManager);
    });
    return *this;
}

App &App::AddSystem(Schedule schedule, void (*func)(entt::registry &, Renderer::Manager &renderer))
{
    _systems[schedule].push_back([=] {
        func(_registry, _renderer);
    });
    return *this;
}

void App::Run()
{

    for (auto system: _systems[Schedule::SETUP]) {
        system();
    }


    // Add loop for setup
    bool isRunning = true;
    while (isRunning) {
        _window.FrameStart();
        _inputManager.Update();

        _inputManager.ProcessEvents(&isRunning);

        // Loop for update
        for (auto system: _systems[Schedule::UPDATE]) {
            system();
        }

        _renderer.SetDrawColor();
        _window.Clear();

        // loop for render
        for (auto system: _systems[Schedule::RENDER]) {
            system();
        }
        //        std::cout << "here" << std::endl;
        _window.LimitFrameRate();
        _window.Present();
    }
}
