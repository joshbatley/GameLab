#pragma once

#include <entt/entt.hpp>
#include <vector>

#include "AssetManager.h"
#include "Engine/Engine.h"
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <typeinfo>

enum Schedule {
    SETUP,
    UPDATE,
    RENDER
};

class App {
public:
    App(const char *title, const int x, const int y, const int w, const int h, const Uint32 flags);

    App &AddPlugin(void (*func)(App *app));
    App &AddSystem(Schedule schedule, void (*func)());
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Asset::Manager assetServer));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Asset::Manager assetServer, Input::Manager Input));
    App &AddSystem(Schedule schedule, void (*func)(entt::registry &reg, Input::Manager Input));
    App &AddSystem(Schedule, void (*func)(entt::registry &reg, Renderer::Manager &render));

    void Run();

private:
    Window::Manager _window;
    Asset::Manager _assetServer;
    Renderer::Manager _renderer;
    entt::registry _registry;
    Input::Manager _inputManager;
    std::unordered_map<Schedule, std::vector<std::function<void()>>> _systems;
};
