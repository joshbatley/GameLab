#pragma once

#include <random>
#include <array>
#include <iostream>
#include <entt/entt.hpp>
#include <FastNoiseLite.h>
#include "Components/Components.h"

class WorldManager {
public:
    WorldManager();

    void LoadNewLevel();
    void Update();
    entt::registry& GetReg();

private:
    int _chunkSize = 64;
    std::array<std::array<std::array<float, 64>, 64>, 5> _chunks = {{}}; // 0 - center, NESW - 1234
    entt::registry _reg;
    FastNoiseLite _noise;

    void _loadLevel();
};