#pragma once

#include <entt/entt.hpp>
#include "Components/Components.h"
#include <FastNoiseLite.h>

class WorldManager {
public:
    WorldManager(entt::registry &reg);
    void Init();

private:
    int _worldSizeX = 80 * 10;
    int _worldSizeY = 45 * 100;
    entt::registry &_reg;
    FastNoiseLite _noise;
    void _loadLevel();
};
