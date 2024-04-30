#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"

class UpdateSystem {
public:
    void Render(entt::registry &reg);
};
