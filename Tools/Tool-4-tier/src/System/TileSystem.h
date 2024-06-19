#pragma once

#include "../Components/Components.h"
#include "Engine.h"
#include "../Events.h"
#include "../Utils/Utils.h"
#include <FastNoiseLite.h>
#include <random>

const std::string SPRITE_TEXTURE_KEY = "spriteMap";

class TileSystem {
public:
    static void Plugin(App *app);

private:
    static void Setup(Engine::World &world, Event::Registry &eventRegistry, Asset::Registry &asset);
    static void ReloadWorld(Engine::World &world, Event::Registry &eventRegistry, RefreshWorldEvent ev);
    static void UpdateTile(Engine::World &world, Event::Registry &eventRegistry, UpdateTileEvent ev);
    static void ApplyRules(Engine::World &world, ApplyRulesEvent ev);
    static void ShowSelectedTile(Engine::World &world, Engine::Resource<GameData> resource);
};