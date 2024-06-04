#include "TileSystem.h"

TileSystem::TileSystem()
{
    _noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    _noise.SetSeed(TileSystem::_generateRandomSeed());
}

void TileSystem::Setup(entt::registry &reg)
{
    reg.emplace<TileArray>(reg.create());
    TileArray &tileArray = reg.get<TileArray>(reg.view<TileArray>().front());
    _generateNoise(tileArray);
}

void TileSystem::Update(entt::registry &reg)
{
    TileArray &tileArray = reg.get<TileArray>(reg.view<TileArray>().front());
    _noise.SetSeed(TileSystem::_generateRandomSeed());
    _generateNoise(tileArray);
}


void TileSystem::Render(entt::registry &reg, Renderer::Manager &render)
{
    TileArray &tileArray = reg.get<TileArray>(reg.view<TileArray>().front());
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto noisePoint = tileArray.Tiles[y][x];

            Tile tile;
            if (noisePoint > 0.2f) {
                tile = TileTypes.at(Land);
            } else if (noisePoint > 0.1f) {
                tile = TileTypes.at(Sand);
            } else {
                tile = TileTypes.at(Water);
            }

            Engine::ivec4 dest = {x * TileSize::Size, y * TileSize::Size, TileSize::Size, TileSize::Size};
            Engine::ivec4 src = {tile.src.x, tile.src.y, 16, 16};

            render.Render(SPRITE_TEXTURE_KEY, src, dest);
        }
    }
}

void TileSystem::_generateNoise(TileArray &tileArray)
{
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            tileArray.Tiles[y][x] = _noise.GetNoise((float)x, (float)y);
        }
    }
}

int TileSystem::_generateRandomSeed()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen();
}