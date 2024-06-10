#include "TileSystem.h"
#include "../Utils/Noise.h"

void TileSystem::Setup(entt::registry &reg, Asset::Manager asset)
{
    Noise &noise = Noise::getInstance();
    reg.emplace<TileArray>(reg.create());
    TileArray &tileArray = reg.get<TileArray>(reg.view<TileArray>().front());
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto &tile = reg.emplace<Tile>(reg.create());
            tileArray.Tiles[y][x] = &tile;
            tile.dest = {x, y};
            tile.data = noise.GetNoise((float)x, (float)y);
            tile.texture = asset.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());
            if (tile.data > 0.2f) {
                tile.src = TileTypes.at(Land).src;
            } else if (tile.data > 0.1f) {
                tile.src = TileTypes.at(Sand).src;
            } else {
                tile.src = TileTypes.at(Water).src;
            }
        }
    }
    //    _generateNoise(tileArray);
}

void TileSystem::Update(entt::registry &reg)
{
    TileArray &tileArray = reg.get<TileArray>(reg.view<TileArray>().front());
    //    _generateNoise(tileArray);
}


void TileSystem::Render(entt::registry &reg, Renderer::Manager &render)
{
    auto view = reg.view<Tile>();
    for (auto entity: view) {
        auto tile = view.get<Tile>(entity);
        Engine::ivec4 dest = {tile.dest.x * TileSize::Size, tile.dest.y * TileSize::Size, TileSize::Size, TileSize::Size};
        Engine::ivec4 src = {tile.src.x, tile.src.y, 16, 16};
        render.Render(tile.texture, src, dest);
    }
}

void TileSystem::_generateNoise(TileArray &tileArray)
{
    Noise &noise = Noise::getInstance();
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto tile = tileArray.Tiles[y][x];
            tile->data = noise.GetNoise((float)x, (float)y);
            if (tile->data > 0.2f) {
                tile->src = TileTypes.at(Land).src;
            } else if (tile->data > 0.1f) {
                tile->src = TileTypes.at(Sand).src;
            } else {
                tile->src = TileTypes.at(Water).src;
            }
        }
    }
}