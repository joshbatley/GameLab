#pragma once

#include "../Alias.h"
#include "../Engine.h"
#include "../Systems/Systems.h"
#include "AssetManager.h"
#include "Dispatcher.h"
#include "InputManager.h"
#include "WindowManager.h"
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <vector>

class App {
public:
    App(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags);

    App &AddPlugin(void (*func)(App *app));
    App &AddSystem(System::Schedule schedule, void (*func)());
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world));
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher));
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Manager &assetServer));
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Input::Manager &Input));
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher, Input::Manager &Input));
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Graphics::Manager &render));

    template<typename EventType>
    App &AddEvent(void (*func)(Engine::World &world, EventType))
    {
        _dispatcher.AddEventReader<EventType>([func, this](EventType ev) {
            func(_registry, ev);
        });
        return *this;
    }

    template<typename EventType>
    App &AddEvent(void (*func)(Engine::World &world, Dispatcher &dispatcher, EventType))
    {
        _dispatcher.AddEventReader<EventType>([func, this](EventType ev) {
            func(_registry, _dispatcher, ev);
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

    Engine::World _registry;
    std::unordered_map<System::Schedule, std::vector<std::function<void()>>> _systems;
};
