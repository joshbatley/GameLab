#include "TileSystem.h"

void TileSystem::Plugin(App *app)
{
    app->AddSystem(System::SETUP, TileSystem::Setup)
      .AddEvent<ReloadEvent>(TileSystem::ReloadWorld)
      .AddEvent<UpdateTileEvent>(TileSystem::UpdateTile);
}

void TileSystem::Setup(Engine::World &world, Asset::Manager &asset)
{
    Noise &noise = Noise::getInstance();
    world.emplace<TileArray>(world.create());
    TileArray &tileArray = world.get<TileArray>(world.view<TileArray>().front());

    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto ent = world.create();
            auto &tile = world.emplace<Tile>(ent);
            auto texture = asset.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());

            auto &sprite = world.emplace<Sprite>(ent, texture, Vec::ivec2 {0, 0}, Vec::ivec2 {16, 16});
            auto &transform = world.emplace<Transform>(ent);

            tileArray.tiles[y][x] = ent;
            transform.translate = {x, y, 0};
            transform.scale = {TileSize::Size, TileSize::Size, 0};
            auto data = noise.GetNoise((float)x, (float)y);

            if (data > 0.2f) {
                sprite.src = TileTypes.at(Land);
            } else if (data > 0.1f) {
                sprite.src = TileTypes.at(Sand);
            } else {
                sprite.src = TileTypes.at(Water);
            }
        }
    }
}

void TileSystem::ReloadWorld(Engine::World &world, ReloadEvent _)
{
    TileArray &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    Noise &noise = Noise::getInstance();

    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto ent = tileArray.tiles[y][x];
            auto &sprite = world.get<Sprite>(ent);
            auto &tile = world.get<Tile>(ent);
            auto data = noise.GetNoise((float)x, (float)y);

            if (data > 0.2f) {
                sprite.src = TileTypes.at(Land);
            } else if (data > 0.1f) {
                sprite.src = TileTypes.at(Sand);
            } else {
                sprite.src = TileTypes.at(Water);
            }
        }
    }
}

void TileSystem::UpdateTile(Engine::World &world, UpdateTileEvent ev)
{
    TileArray &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    auto ent = tileArray.tiles[ev.y][ev.x];
    auto &sprite = world.get<Sprite>(ent);
    sprite.src = TileTypes.at(Water);
}
