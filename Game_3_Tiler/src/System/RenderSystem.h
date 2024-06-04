#pragma once

#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "entt/entt.hpp"

class RenderSystem {
public:
    static void Render(entt::registry &reg, Renderer::Manager &render);
};
