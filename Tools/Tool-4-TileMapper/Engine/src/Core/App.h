#pragma once

#include "AssetHandler.h"
#include "EventHandler.h"
#include "GraphicsHandler.h"
#include "InputManager.h"
#include "Resource.h"
#include "Systems/RenderSystem.h"
#include "Systems/Systems.h"
#include "Utils/AppSettings.h"
#include "WindowManager.h"

#include <functional>
#include <vector>

class App {
public:
    App(const Window::Config &config);
    void Run();

    App &AddPlugin(void (*func)(App *app))
    {
        func(this);
        return *this;
    }

    template<typename ResourceType>
    App &AddResource(ResourceType &resource)
    {
        _resourceHandler.add<ResourceType>(resource);
        return *this;
    }
    template<typename ResourceType>
    App &AddResource()
    {
        _resourceHandler.add<ResourceType>();
        return *this;
    }

    template<typename EventType>
    App &AddSystem(void (*func)(Engine::World &world, EventType))
    {
        _eventHandler.AddReader<EventType>([func, this](EventType ev) {
            func(_registry, ev);
        });
        return *this;
    }
    template<typename EventType>
    App &AddSystem(void (*func)(Engine::World &world, Event::Handler &eventHandler, EventType))
    {
        _eventHandler.AddReader<EventType>([func, this](EventType ev) {
            func(_registry, _eventHandler, ev);
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
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventHandler))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventHandler);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Handler &assetHandler))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _assetHandler);
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
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventHandler, Input::Manager &Input))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventHandler, _inputManager);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventHandler, Asset::Handler &assetHandler))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventHandler, _assetHandler);
        });
        return *this;
    }
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Graphics::Handler &graphics))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _graphicsHandler);
        });
        return *this;
    }

    template<typename... ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Engine::Resource<ResourceType...> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _resourceHandler.get<ResourceType...>());
        });
        return *this;
    }
    template<typename... ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventHandler, Engine::Resource<ResourceType...> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventHandler, _resourceHandler.get<ResourceType...>());
        });
        return *this;
    }
    template<typename... ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Asset::Handler &assetHandler, Engine::Resource<ResourceType...> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _assetHandler, _resourceHandler.get<ResourceType...>());
        });
        return *this;
    }
    template<typename... ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Input::Manager &Input, Engine::Resource<ResourceType...> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _inputManager, _resourceHandler.get<ResourceType...>());
        });
        return *this;
    }
    template<typename... ResourceType>
    App &AddSystem(System::Schedule schedule, void (*func)(Engine::World &world, Event::Handler &eventHandler, Input::Manager &Input, Engine::Resource<ResourceType...> resource))
    {
        _systems[schedule].emplace_back([=, this] {
            func(_registry, _eventHandler, _inputManager, _resourceHandler.get<ResourceType...>());
        });
        return *this;
    }

private:
    Engine::World _registry;
    Window::Manager _windowManager;
    Input::Manager _inputManager;
    Event::Handler _eventHandler;
    Asset::Handler _assetHandler;
    Graphics::Handler _graphicsHandler;
    Resource::Handler _resourceHandler;
    std::unordered_map<System::Schedule, std::vector<std::function<void()>>> _systems;
};