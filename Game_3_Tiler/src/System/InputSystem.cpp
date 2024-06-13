#include "InputSystem.h"

void InputSystem::Plugin(App *app)
{
    app->AddSystem(System::SETUP, InputSystem::SetupCursor)
      .AddSystem(System::UPDATE, InputSystem::GenerateNewMap)
      .AddSystem(System::UPDATE, InputSystem::CursorUpdate)
      .AddSystem(System::UPDATE, InputSystem::UpdateTile)
      .AddSystem(System::UPDATE, InputSystem::ChangeTileSelected);
}

void InputSystem::SetupCursor(Engine::World &world, Asset::Manager &asset)
{
    auto ent = world.create();
    auto texture = asset.LoadTexture(CURSOR_TEXTURE_KEY, (std::string(SPROUT_LANDS) + "/ui/icons/select.png").c_str());

    world.emplace<Cursor>(ent);
    world.emplace<Sprite>(ent, texture, Vec::ivec2 {0, 0}, Vec::ivec2 {32, 32});
    world.emplace<Transform>(ent, Vec::ivec3 {0, 0, 10}, Vec::ivec3 {TileSize::Size, TileSize::Size, 0});
}

void InputSystem::CursorUpdate(Engine::World &world, Input::Manager &input)
{
    auto [mouseX, mouseY] = input.GetMousePosition();
    auto view = world.view<Cursor, Transform>();
    for (auto ent: view) {
        auto &transform = view.get<Transform>(ent);
        auto x = mouseX / 32;
        auto y = mouseY / 32;
        transform.translate = {x * TileSize::Size, y * TileSize::Size, 10};
    }
}

void InputSystem::GenerateNewMap(Engine::World &_, EventRegistry &eventRegistry, Input::Manager &input)
{
    auto &noise = Noise::getInstance();
    if (input.IsActionPressed(Input::ACTION3)) {
        noise.SetRandomSeed();
        eventRegistry.Send(ApplyRulesEvent {});
        eventRegistry.Send(RefreshWorldEvent {});
    }
}

void InputSystem::ChangeTileSelected(Engine::World &_, Input::Manager &input, Engine::Resource<GameData> resource)
{
    if (input.IsActionDown(Input::NUM1)) {
        resource.data.type = TileType::Water;
    }
    if (input.IsActionDown(Input::NUM2)) {
        resource.data.type = TileType::Sand;
    }
    if (input.IsActionDown(Input::NUM3)) {
        resource.data.type = TileType::Land;
    }
}

void InputSystem::UpdateTile(Engine::World &world, EventRegistry &eventRegistry, Input::Manager &input, Engine::Resource<GameData> resource)
{
    auto gameDate = resource.into();
    auto view = world.view<Cursor, Transform>();
    for (auto ent: view) {
        if (input.IsActionDown(Input::ACTION1)) {
            auto &transform = view.get<Transform>(ent);
            auto x = transform.translate.x / TileSize::Size;
            auto y = transform.translate.y / TileSize::Size;
            eventRegistry.Send(UpdateTileEvent {x, y, gameDate.type});
        }
    }
}
