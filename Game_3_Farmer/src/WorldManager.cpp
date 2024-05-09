#include "WorldManager.h"

int GenerateRandomSeed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen();
}

WorldManager::WorldManager()
{
    _noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    _noise.SetSeed(GenerateRandomSeed());
    _reg = entt::registry();

    _reg.emplace<Camera>(_reg.create());

    for (int i = 0; i < _chunks.size(); i++) {
        for (int y = 0; y < _chunkSize; y++) {
            for (int x = 0; x < _chunkSize; x++) {
                int xpos = x;
                int ypos = y;

                if (i == 1) {
                    ypos -= _chunkSize;
                }
                if (i == 2) {
                   xpos += _chunkSize;
                }
                if (i == 3) {
                    ypos += _chunkSize;
                }
                if (i == 4) {
                    xpos -= _chunkSize;
                }
                auto ent = _reg.create();
                _reg.emplace<Position>(ent, xpos, ypos);
                _reg.emplace<Tile>(ent);
            }
        }
    }
}

void WorldManager::LoadNewLevel()
{
    _noise.SetSeed(GenerateRandomSeed());
}

void WorldManager::LoadLevel()
{
    WorldManager::_loadLevel();
}

void WorldManager::_loadLevel()
{
    auto t = setupTileTypes();
    Camera &camera = _reg.get<Camera>(_reg.view<Camera>().front());

    for (int c = 0; c < _chunks.size(); c++) {
        for (int y = 0; y < _chunkSize; y++) {
            for (int x = 0; x < _chunkSize; x++) {
                float xpos = x + camera.pos.x;
                float ypos = y + camera.pos.y;

                if (c == 1) {
                    ypos -= (float)_chunkSize;
                }
                if (c == 2) {
                    xpos += (float)_chunkSize;
                }
                if (c == 3) {
                    ypos += (float)_chunkSize;
                }
                if (c == 4) {
                    xpos -= (float)_chunkSize;
                }
                _chunks[c][y][x] = _noise.GetNoise(xpos, ypos);
            }
        }
    }

    for (auto entity : _reg.view<Position>())
    {
        auto& tile = _reg.get<Position>(entity);
        int x = tile.Dest.x;
        int y = tile.Dest.y;
        int chunk = 0;

        if (x < _chunkSize && y < _chunkSize) {
            chunk = 0;
        }
        if (x >= 0 && y < 0) {
            chunk = 1;
        }
        if (x >= _chunkSize && y < _chunkSize) {
            chunk = 2;
        }
        if (x < _chunkSize && y >= _chunkSize) {
            chunk = 3;
        }
        if (x < 0 && y < _chunkSize) {
            chunk = 4;
        }

        auto xpos = ((tile.Dest.x % _chunkSize) + _chunkSize) %_chunkSize;
        auto ypos = ((tile.Dest.y % _chunkSize) + _chunkSize) %_chunkSize;
        auto noisePoint = _chunks[chunk][ypos][xpos];

        if (noisePoint > 0.2f) {
            _reg.replace<Tile>(entity, t[Land]);
        } else if (noisePoint > 0.1f) {
            _reg.replace<Tile>(entity, t[Sand]);
        } else {
            _reg.replace<Tile>(entity, t[Water]);
        }
    }
}

entt::registry& WorldManager::GetReg()
{
    return _reg;
}

