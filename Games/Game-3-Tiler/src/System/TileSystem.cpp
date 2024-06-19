#include "TileSystem.h"

void TileSystem::Plugin(App *app)
{
    app->AddSystem(System::SETUP, TileSystem::Setup)
      .AddEvent(TileSystem::ApplyRules)
      .AddEvent(TileSystem::ReloadWorld)
      .AddEvent(TileSystem::UpdateTile)
      .AddSystem(System::UPDATE, ShowSelectedTile);
}

void TileSystem::Setup(Engine::World &world, EventRegistry &eventRegistry, Asset::Manager &asset)
{
    auto texture = asset.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());
    auto borderTexture = asset.LoadTexture(SPRITE_TEXTURE_KEY + "12", (std::string(SPROUT_LANDS) + "/ui/dialog/borders.png").c_str());

    auto selectedBorder = world.create();
    world.emplace<Sprite>(selectedBorder, borderTexture, Vec::ivec2 {104, 8}, Vec::ivec2 {32, 32});
    world.emplace<Transform>(selectedBorder, Vec::ivec3 {-32, -32, 20}, Vec::ivec3 {256, 256, 0});

    auto selectedTile = world.create();
    world.emplace<Sprite>(selectedTile, texture, TileTypes.at(Water), Vec::ivec2 {16, 16});
    world.emplace<Transform>(selectedTile, Vec::ivec3 {40, 40, 30}, Vec::ivec3 {112, 112, 0});
    world.emplace<SelectedTile>(selectedTile);

    auto &noise = Noise::getInstance();
    world.emplace<TileArray>(world.create());

    auto &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto ent = world.create();
            tileArray.tiles[y][x] = ent;

            auto &tile = world.emplace<Tile>(ent);
            auto &sprite = world.emplace<Sprite>(ent, texture, Vec::ivec2 {0, 0}, Vec::ivec2 {16, 16});
            auto data = noise.GetNoise((float)x, (float)y);

            world.emplace<Transform>(ent, Vec::ivec3 {x * TileSize::Size, y * TileSize::Size, 0}, Vec::ivec3 {TileSize::Size, TileSize::Size, 0});
            if (data > 0.2f) {
                tile.type = Land;
                sprite.src = TileTypes.at(Land);
            } else if (data > 0.1f) {
                tile.type = Sand;
                sprite.src = TileTypes.at(Sand);
            } else {
                tile.type = Water;
                sprite.src = TileTypes.at(Water);
            }
        }
    }

    eventRegistry.Send(ApplyRulesEvent {});
}

void TileSystem::ReloadWorld(Engine::World &world, EventRegistry &eventRegistry, RefreshWorldEvent _)
{
    auto &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    auto &noise = Noise::getInstance();

    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto ent = tileArray.tiles[y][x];
            auto &sprite = world.get<Sprite>(ent);
            auto &tile = world.get<Tile>(ent);
            auto data = noise.GetNoise((float)x, (float)y);

            if (data > 0.2f) {
                tile.type = Land;
                sprite.src = TileTypes.at(Land);
            } else if (data > 0.1f) {
                tile.type = Sand;
                sprite.src = TileTypes.at(Sand);
            } else {
                tile.type = Water;
                sprite.src = TileTypes.at(Water);
            }
        }
    }
    eventRegistry.Send(ApplyRulesEvent {});
}

void TileSystem::UpdateTile(Engine::World &world, EventRegistry &eventRegistry, UpdateTileEvent ev)
{
    auto &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    auto ent = tileArray.tiles[ev.y][ev.x];
    auto &sprite = world.get<Sprite>(ent);
    auto &tile = world.get<Tile>(ent);

    sprite.src = TileTypes.at(ev.type);
    tile.type = ev.type;

    eventRegistry.Send(ApplyRulesEvent {});
}

bool isValidIndex(int index, int maxIndex)
{
    return index >= 0 && index < maxIndex;
}

Vec::ivec2 newSrc(TileType current, TileType up, TileType down, TileType left, TileType right)
{
    auto &rules = Rules.at(current);
    for (auto rule: rules) {
        auto test = rule.rule;
        auto upTest = up == DEFAULT ? true : up == test[0][1];
        auto downTest = down == DEFAULT ? true : down == test[2][1];
        auto leftTest = left == DEFAULT ? true : left == test[1][0];
        auto rightTest = right == DEFAULT ? true : right == test[1][2];
        if (upTest && downTest && leftTest && rightTest) {
            return rule.newSrc;
        }
    }
    return {0, 0};
}

void TileSystem::ApplyRules(Engine::World &world, ApplyRulesEvent ev)
{
    auto &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {
            auto ent = tileArray.tiles[y][x];
            auto type = world.get<Tile>(ent).type;
            auto &sprite = world.get<Sprite>(ent);

            auto typeUp = (isValidIndex(y - 1, TileSize::Y)) ? world.get<Tile>(tileArray.tiles[y - 1][x]).type : TileType::DEFAULT;
            auto typeDown = (isValidIndex(y + 1, TileSize::Y)) ? world.get<Tile>(tileArray.tiles[y + 1][x]).type : TileType::DEFAULT;
            auto typeLeft = (isValidIndex(x - 1, TileSize::X)) ? world.get<Tile>(tileArray.tiles[y][x - 1]).type : TileType::DEFAULT;
            auto typeRight = (isValidIndex(x + 1, TileSize::X)) ? world.get<Tile>(tileArray.tiles[y][x + 1]).type : TileType::DEFAULT;

            auto src = newSrc(type, typeUp, typeDown, typeLeft, typeRight);
            if (!(src.x == 0 && src.y == 0)) {
                sprite.src = src;
            }
        }
    }
}

void TileSystem::ShowSelectedTile(Engine::World &world, Engine::Resource<GameData> resource)
{
    auto gameDate = resource.into();
    auto view = world.view<SelectedTile, Sprite>();
    for (auto ent: view) {
        auto &sprite = view.get<Sprite>(ent);
        auto &tile = view.get<SelectedTile>(ent);
        sprite.src = TileTypes.at(gameDate.type);
        tile.type = gameDate.type;
    }
}