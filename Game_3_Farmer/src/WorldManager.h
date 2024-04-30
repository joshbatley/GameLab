#pragma once

#include <entt/entt.hpp>
#include "Components/Components.h"

class WorldManager {
public:
    WorldManager();
    void Init(entt::registry &reg);
};
