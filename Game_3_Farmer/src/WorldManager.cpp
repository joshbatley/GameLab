#include "WorldManager.h"

WorldManager::WorldManager(entt::registry &reg) : _reg(reg)
{
    _noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
}

void WorldManager::Init()
{
    WorldManager::_loadLevel();
}

void WorldManager::_loadLevel()
{
    for (int y = 0; y < 128; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            auto ent = _reg.create();
            _reg.emplace<Tile>(ent, x, y);
        }
    }
}