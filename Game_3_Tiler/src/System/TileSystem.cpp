#include "TileSystem.h"

void TileSystem::Plugin(App *app)
{
    app->AddSystem(System::SETUP, TileSystem::Setup)
      .AddEvent<ApplyRulesEvent>(TileSystem::ApplyRules)
      .AddEvent<RefreshWorldEvent>(TileSystem::ReloadWorld)
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
            auto texture = asset.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());
            auto &tile = world.emplace<Tile>(ent);
            auto &sprite = world.emplace<Sprite>(ent, texture, Vec::ivec2 {0, 0}, Vec::ivec2 {16, 16});
            auto &transform = world.emplace<Transform>(ent);

            tileArray.tiles[y][x] = ent;
            transform.translate = {x, y, 0};
            transform.scale = {TileSize::Size, TileSize::Size, 0};
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
}

void TileSystem::ReloadWorld(Engine::World &world, Dispatcher &dispatcher, RefreshWorldEvent _)
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
    dispatcher.Send(ApplyRulesEvent {});
}

void TileSystem::UpdateTile(Engine::World &world, Dispatcher &dispatcher, UpdateTileEvent ev)
{
    TileArray &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    auto ent = tileArray.tiles[ev.y][ev.x];
    auto &sprite = world.get<Sprite>(ent);
    auto &tile = world.get<Tile>(ent);
    sprite.src = TileTypes.at(Water);
    tile.type = Type::Water;
    dispatcher.Send(ApplyRulesEvent {});
}

bool isValidIndex(int index, int maxIndex)
{
    return index >= 0 && index < maxIndex;
}

Vec::ivec2 newSrc(Type current, Type up, Type down, Type left, Type right)
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
    TileArray &tileArray = world.get<TileArray>(world.view<TileArray>().front());
    for (int y = 0; y < TileSize::Y; y++) {
        for (int x = 0; x < TileSize::X; x++) {

            auto ent = tileArray.tiles[y][x];
            auto type = world.get<Tile>(ent).type;
            auto &sprite = world.get<Sprite>(ent);

            auto typeUp = (isValidIndex(y - 1, TileSize::Y)) ? world.get<Tile>(tileArray.tiles[y - 1][x]).type : Type::DEFAULT;
            auto typeDown = (isValidIndex(y + 1, TileSize::Y)) ? world.get<Tile>(tileArray.tiles[y + 1][x]).type : Type::DEFAULT;
            auto typeLeft = (isValidIndex(x - 1, TileSize::X)) ? world.get<Tile>(tileArray.tiles[y][x - 1]).type : Type::DEFAULT;
            auto typeRight = (isValidIndex(x + 1, TileSize::X)) ? world.get<Tile>(tileArray.tiles[y][x + 1]).type : Type::DEFAULT;

            auto src = newSrc(type, typeUp, typeDown, typeLeft, typeRight);
            if (!(src.x == 0 && src.y == 0)) {
                sprite.src = src;
            }
        }
    }
}
