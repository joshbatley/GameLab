#pragma once

#include "../Systems/Systems.h"
#include "../Systems/RenderSystem.h"
#include "AssetHandler.h"
#include "EventHandler.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "GraphicsHandler.h"
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <vector>

class App {
public:
    App(Window::Config config);
    void Run();

    App &AddPlugin(void (*func)(App *app))
    {
        func(this);
        return *this;
    }
    template<typename ResourceType>
    App &AddResource(ResourceType resource)
    {
        _resources[typeid(ResourceType)] = Engine::Resource<ResourceType> {resource};
        return *this;
    }
    template<typename EventType>
    App &AddEvent(void (*func)(Engine::World &world, EventType))
    {
        _eventRegistry.AddReader<EventType>([func, this](EventType ev) {
            func(_registry, ev);
        });
        return *this;
    }
    template<typename EventType>
    App &AddEvent(void (*func)(Engine::World &world, Event::Handler &eventRegistry, EventType))
    {
        _eventRegistry.AddReader<EventType>([func, this](EventType ev) {
            func(_registry, _eventRegistry, ev);
        });
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
        _systems[schedule].emplace_back([=, this] {
            func(_registry);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventRegistry))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventRegistry);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Handler &assetRegistry))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _assetRegistry);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Input::Manager &Input))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _inputManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventRegistry, Input::Manager &Input))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventRegistry, _inputManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventRegistry, Asset::Handler &assetRegistry))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventRegistry, _assetRegistry);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Graphics::Handler &graphics))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _graphics);
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventRegistry, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventRegistry, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Handler &assetRegistry, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _assetRegistry, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Input::Manager &Input, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _inputManager, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }
    template<typename ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventRegistry, Input::Manager &Input, Engine::Resource<ResourceType> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventRegistry, _inputManager, std::any_cast<Engine::Resource<ResourceType>>(_resources[typeid(ResourceType)]));
        });
        return *this;
    }

private:
    Window::Manager _window;
    Asset::Handler _assetRegistry;
    Graphics::Handler _graphics;
    Input::Manager _inputManager;
    Event::Handler _eventRegistry;
    Engine::World _registry;
    std::unordered_map<System::Schedule, std::vector<std::function<void()>>> _systems;
    std::map<std::type_index, std::any> _resources = {};
};
