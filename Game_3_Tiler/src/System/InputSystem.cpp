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

void GenerateNewMap(entt::registry &reg, Dispatcher &dispatcher, Input::Manager input)
{
    Noise &noise = Noise::getInstance();
    if (input.IsActionPressed(Input::ACTION3)) {
        noise.SetRandomSeed();
        dispatcher.EnqueueEvent<ReloadEvent>(ReloadEvent {});
    }
}

void UpdateTile(entt::registry &reg, Dispatcher &dispatcher, Input::Manager input)
{
    Cursor &cursor = reg.get<Cursor>(reg.view<Cursor>().front());
    if (input.IsActionDown(Input::ACTION1)) {
        auto x = cursor.Pos.x;
        auto y = cursor.Pos.y;
        dispatcher.EnqueueEvent<UpdateTileEvent>(UpdateTileEvent {x, y});
    }
}

void InputSystem::Plugin(App *app)
{
    app->AddSystem(UPDATE, GenerateNewMap)
      .AddSystem(UPDATE, CursorUpdate)
      .AddSystem(UPDATE, UpdateTile);
}
