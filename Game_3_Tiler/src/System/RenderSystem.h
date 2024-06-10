#pragma once

#include "../AssetManager.h"
#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "entt/entt.hpp"

class RenderSystem {
public:
    static void Setup(entt::registry &reg, Asset::Manager manager);
    static void Render(entt::registry &reg, Renderer::Manager &renderer);
};
