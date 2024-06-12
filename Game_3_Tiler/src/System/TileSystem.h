#pragma once

#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "../Events.h"
#include "../Utils/Utils.h"
#include <FastNoiseLite.h>
#include <random>

const std::string SPRITE_TEXTURE_KEY = "spriteMap";

class TileSystem {
public:
    static void Plugin(App *app);

private:
    static void Setup(Engine::World &world, Asset::Manager asset);
    static void ReloadWorld(Engine::World &world, ReloadEvent ev);
    static void UpdateTile(Engine::World &world, UpdateTileEvent ev);
};