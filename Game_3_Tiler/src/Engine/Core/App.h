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
    App(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags, bool showCursor, bool relativeMouse);
    App(Window::Config config);

    App &AddPlugin(void (*func)(App *app))
    {
        func(this);
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)())
    {
        _systems[schedule].emplace_back([=] {
            func();
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _dispatcher);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Manager &assetManager))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _assetManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Input::Manager &Input))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _inputManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher, Input::Manager &Input))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _dispatcher, _inputManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher, Asset::Manager &assetManager))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _dispatcher, _assetManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Graphics::Manager &render))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _renderer);
        });
        return *this;
    }

    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _dispatcher, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Manager &assetManager, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _assetManager, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Input::Manager &Input, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _inputManager, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Dispatcher &dispatcher, Input::Manager &Input, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=] {
            func(_registry, _dispatcher, _inputManager, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }

    template<typename ResourceType>
    App &AddResource(ResourceType &resource)
    {
        _resources[typeid(ResourceType)] = Engine::Resource<ResourceType> {resource};
        return *this;
    }

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
    std::map<std::type_index, std::any> _resources = {};
};
