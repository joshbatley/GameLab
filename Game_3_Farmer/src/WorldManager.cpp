#include "WorldManager.h"

int GenerateRandomSeed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen();
}

WorldManager::WorldManager()
{
    _noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    _noise.SetSeed(GenerateRandomSeed());
}

void WorldManager::LoadLevel()
{
    _reg = entt::registry();
    _noise.SetSeed(GenerateRandomSeed());

    auto cam = _reg.create();
    _reg.emplace<Camera>(cam);
    WorldManager::_loadLevel();
}

void WorldManager::_loadLevel()
{
    auto t = setupTileTypes();
    for (int y = 0; y < _worldSizeY; y++)
    {
        for (int x = 0; x < _worldSizeX; x++)
        {
            auto q = _noise.GetNoise((float)x, (float)y);
            auto ent = _reg.create();
            if (q <= 0.2f) {
                 _reg.emplace<Tile>(ent, t[Water]);
            } else {
                _reg.emplace<Tile>(ent, t[Land]);
            }
            _reg.emplace<Position>(ent, x, y);
        }
    }
}
entt::registry& WorldManager::GetReg()
{
    return _reg;
}

