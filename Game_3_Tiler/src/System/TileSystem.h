#pragma once

#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "../System/InputSystem.h"
#include "../Utils/Utils.h"
#include <FastNoiseLite.h>
#include <entt/entt.hpp>
#include <random>

class TileSystem final {
public:
    TileSystem();
    void Setup(entt::registry &reg);
    void Update(entt::registry &reg);
    void Render(entt::registry &reg, Renderer::Manager &render);

private:
    void _generateNoise(TileArray &tileArray);
    static int _generateRandomSeed();
    FastNoiseLite _noise;
};