#pragma once

#include "../Components/Components.h"
#include "../Events.h"
#include "../System/InputSystem.h"
#include "../Utils/Utils.h"
#include <Engine.h>
#include <FastNoiseLite.h>
#include <random>

class TileSystem {
public:
    static void Plugin(App *app);

private:
    static void Setup(World &world, Asset::Manager asset);
    static void ReloadWorld(World &world, ReloadEvent ev);
    static void UpdateTile(World &world, UpdateTileEvent ev);
};