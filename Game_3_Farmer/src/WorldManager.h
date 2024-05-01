#pragma once

#include <entt/entt.hpp>
#include "Components/Components.h"
#include <FastNoiseLite.h>

class WorldManager {
public:
    WorldManager(entt::registry &reg);
    void Init();

private:
    entt::registry &_reg;
    FastNoiseLite _noise;
    void _loadLevel();
};
