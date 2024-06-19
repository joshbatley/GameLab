#pragma once

#include "Utils/Utils.h"

struct RefreshWorldEvent {
    int id;
};

struct ApplyRulesEvent {
    int id2 = 1;
};

struct UpdateTileEvent {
    int x;
    int y;
    TileType type;
};

struct GameData {
    TileType type = TileType::Water;
};