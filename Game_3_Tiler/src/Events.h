#pragma once

struct RefreshWorldEvent {
    int id;
};

struct ApplyRulesEvent {
    int id2 = 1;
};

struct UpdateTileEvent {
    int x;
    int y;
};