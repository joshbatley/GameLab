#include "InputSystem.h"


void InputSystem::Update(entt::registry &reg, entt::dispatcher &dispatcher)
{
    if (_input.IsActionDown(Input::ACTION1)) {
        auto x = _input.GetMousePosition().x / TileSize::Size;
        auto y = _input.GetMousePosition().y / TileSize::Size;
        dispatcher.enqueue<MouseEvent>(x, y);
        //        tileArray.Tiles[y][x] = 1;
    }

    if (_input.IsActionPressed(Input::ACTION3)) {

        dispatcher.enqueue<ReloadEvent>(4);
    }

    auto [mouseX, mouseY] = _input.GetMousePosition();

    auto entities = reg.view<Cursor>();
    for (auto ent: entities) {
        auto &cursor = reg.get<Cursor>(ent);
        auto x = lerp(cursor.Pos.x, mouseX / TileSize::Size, cursor.Speed);
        auto y = lerp(cursor.Pos.y, mouseY / TileSize::Size, cursor.Speed);
        cursor.Pos = {x, y};
    }
}