#include "InputSystem.h"

void InputSystem::Plugin(App *app)
{
    app->AddSystem(System::SETUP, InputSystem::SetupCursor)
      .AddSystem(System::UPDATE, InputSystem::GenerateNewMap)
      .AddSystem(System::UPDATE, InputSystem::CursorUpdate)
      .AddSystem(System::UPDATE, InputSystem::UpdateTile);
}

void InputSystem::SetupCursor(Engine::World &world, Asset::Manager asset)
{
    auto ent = world.create();
    world.emplace<Cursor>(ent);
    auto texture = asset.LoadTexture(CURSOR_TEXTURE_KEY, (std::string(SPROUT_LANDS) + "/ui/icons/select.png").c_str());
    world.emplace<Sprite>(ent, texture, Vec::ivec2 {0, 0}, Vec::ivec2 {32, 32});
    world.emplace<Transform>(ent, Vec::ivec3 {0, 0, 10}, Vec::ivec3 {TileSize::Size, TileSize::Size, 0});
}

void InputSystem::CursorUpdate(Engine::World &world, Input::Manager input)
{
    auto [mouseX, mouseY] = input.GetMousePosition();
    auto view = world.view<Cursor, Transform>();
    for (auto ent: view) {
        auto &transform = view.get<Transform>(ent);
        transform.Translate = {mouseX / TileSize::Size, mouseY / TileSize::Size, 10};
    }
}

void InputSystem::GenerateNewMap(Engine::World &world, Dispatcher &dispatcher, Input::Manager input)
{
    Noise &noise = Noise::getInstance();
    if (input.IsActionPressed(Input::ACTION3)) {
        noise.SetRandomSeed();
        dispatcher.Send<ReloadEvent>(ReloadEvent {});
    }
}

void InputSystem::UpdateTile(Engine::World &world, Dispatcher &dispatcher, Input::Manager input)
{
    auto view = world.view<Cursor, Transform>();
    for (auto ent: view) {
        if (input.IsActionDown(Input::ACTION1)) {
            auto &transform = view.get<Transform>(ent);
            auto x = transform.Translate.x;
            auto y = transform.Translate.y;
            dispatcher.Send<UpdateTileEvent>(UpdateTileEvent {x, y});
        }
    }
}
