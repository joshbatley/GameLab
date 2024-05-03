#pragma once

#include <entt/entt.hpp>
#include <random>
#include <FastNoiseLite.h>
#include "Components/Components.h"

class WorldManager {
public:
    WorldManager();
    void LoadLevel();
    entt::registry& GetReg();

private:
    int _worldSizeX = 80 * 10;
    int _worldSizeY = 45 * 100;
    entt::registry _reg;
    FastNoiseLite _noise;
    void _loadLevel();
};
