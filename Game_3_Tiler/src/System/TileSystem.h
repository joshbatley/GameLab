#pragma once

#include "../App.h"
#include "../AssetManager.h"
#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "../System/InputSystem.h"
#include "../Utils/Utils.h"
#include <FastNoiseLite.h>
#include <entt/entt.hpp>
#include <random>

class TileSystem final {
public:
    static void Setup(entt::registry &reg, Asset::Manager asset);
    static void ReloadWorld(entt::registry &reg, ReloadEvent reloadEvent);
    static void UpdateTile(entt::registry &reg, UpdateTileEvent ev);
    static void Render(entt::registry &reg, Renderer::Manager &render);

private:
    static void _generateNoise(TileArray &tileArray);
};