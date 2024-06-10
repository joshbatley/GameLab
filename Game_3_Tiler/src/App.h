#pragma once

#include "AssetManager.h"
#include "Dispatcher.h"
#include "Engine/Engine.h"
#include <entt/entt.hpp>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <vector>

enum Schedule {
    SETUP,
    UPDATE,
    RENDER
};

struct ReloadEvent {
    int id;
};

struct UpdateTileEvent {
    int x;
    int y;
};

class App {
public:
    App(const char *title, int x, int y, int w, int h, Uint32 flags);

    App &AddPlugin(void (*func)(App *app));

    template<typename EventType>
    App &AddEvent(void (*func)(entt::registry &reg, EventType))
    {
        _dispatcher.template AddEventListener<EventType>([=](EventType ev) {
            func(_registry, ev);
        });
        return *this;
    }

    App &AddSystem(Schedule schedule, void (*func)());
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Dispatcher &dispatcher));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Asset::Manager assetServer));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Input::Manager Input));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Dispatcher &dispatcher, Input::Manager Input));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Renderer::Manager &render));

    void Run();

private:
    Window::Manager _window;
    Asset::Manager _assetManager;
    Renderer::Manager _renderer;
    Input::Manager _inputManager;
    Dispatcher _dispatcher;

    entt::registry _registry;
    std::unordered_map<Schedule, std::vector<std::function<void()>>> _systems;
};
