#pragma once

#include <entt/entt.hpp>
#include "../Engine/Engine.h"
#include "../Components/Components.h"

class Systems {
public:
    void Update(entt::registry &reg);
    void Render(entt::registry &reg, Renderer::Manager &render);
};
