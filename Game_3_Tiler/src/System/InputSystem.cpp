#include "InputSystem.h"

void CursorUpdate(entt::registry &reg, Input::Manager input)
{
    auto [mouseX, mouseY] = input.GetMousePosition();
    auto entities = reg.view<Cursor>();
    for (auto ent: entities) {
        auto &cursor = reg.get<Cursor>(ent);
        auto x = lerp(cursor.Pos.x, mouseX / TileSize::Size, cursor.Speed);
        auto y = lerp(cursor.Pos.y, mouseY / TileSize::Size, cursor.Speed);
        cursor.Pos = {x, y};
    }
}

void GenerateNewMap(entt::registry &reg, Input::Manager input)
{
    Noise &noise = Noise::getInstance();
    if (input.IsActionPressed(Input::ACTION3)) {
        noise.SetRandomSeed();
    }
}

void UpdateTile(entt::registry &reg, Input::Manager input)
{
    TileArray &tileArray = reg.get<TileArray>(reg.view<TileArray>().front());
    if (input.IsActionDown(Input::ACTION1)) {
        auto x = input.GetMousePosition().x / TileSize::Size;
        auto y = input.GetMousePosition().y / TileSize::Size;
        auto tile = tileArray.Tiles[y][x];
        tile->src = TileTypes.at(Land).src;
    }
}

void InputSystem::Plugin(App *app)
{
    app->AddSystem(UPDATE, GenerateNewMap)
      .AddSystem(UPDATE, CursorUpdate)
      .AddSystem(UPDATE, UpdateTile);
}
