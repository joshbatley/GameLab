#pragma once

#include "AssetManager.h"
#include "Dispatcher.h"
#include "Includes.h"
#include "InputManager.h"
#include "WindowManager.h"
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <vector>

using World = entt::registry;
using Entity = entt::entity;

enum Schedule {
    SETUP,
    UPDATE,
    RENDER
};


class App {
public:
    App(const char *title, int x, int y, int w, int h, Uint32 flags);

    App &AddPlugin(void (*func)(App *app));
    App &AddSystem(Schedule schedule, void (*func)());
    App &AddSystem(Schedule schedule, void (*func)(World &world));
    App &AddSystem(Schedule schedule, void (*func)(World &world, Dispatcher &dispatcher));
    App &AddSystem(Schedule schedule, void (*func)(World &world, Asset::Manager assetServer));
    App &AddSystem(Schedule schedule, void (*func)(World &world, Input::Manager Input));
    App &AddSystem(Schedule schedule, void (*func)(World &world, Dispatcher &dispatcher, Input::Manager Input));
    App &AddSystem(Schedule schedule, void (*func)(World &world, Graphics::Manager &render));
    template<typename EventType>
    App &AddEvent(void (*func)(World &world, EventType))
    {
        _dispatcher.AddEventReader<EventType>([func, this](EventType ev) {
            func(_registry, ev);
        });
        return *this;
    }

    void Run();

private:
    Window::Manager _window;
    Asset::Manager _assetManager;
    Graphics::Manager _renderer;
    Input::Manager _inputManager;
    Dispatcher _dispatcher;

    World _registry;
    std::unordered_map<Schedule, std::vector<std::function<void()>>> _systems;
};
