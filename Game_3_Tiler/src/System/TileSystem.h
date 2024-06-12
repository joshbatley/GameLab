#pragma once

#include "../App.h"
#include "../AssetManager.h"
#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "../Events.h"
#include "../System/InputSystem.h"
#include "../Utils/Utils.h"
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