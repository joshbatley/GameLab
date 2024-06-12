#include "InputSystem.h"

void InputSystem::Plugin(App *app)
{
    app->AddSystem(SETUP, InputSystem::SetupCursor)
      .AddSystem(UPDATE, InputSystem::GenerateNewMap)
      .AddSystem(UPDATE, InputSystem::CursorUpdate)
      .AddSystem(UPDATE, InputSystem::UpdateTile);
}

void InputSystem::SetupCursor(World &world, Asset::Manager asset)
{
    auto ent = world.create();
    world.emplace<Cursor>(ent);
    auto texture = asset.LoadTexture(CURSOR_TEXTURE_KEY, (std::string(SPROUT_LANDS) + "/ui/icons/select.png").c_str());
    world.emplace<Sprite>(ent, texture, Engine::ivec2 {0, 0}, Engine::ivec2 {32, 32});
    world.emplace<Transform>(ent, Engine::ivec3 {0, 0, 10});
}

void InputSystem::CursorUpdate(World &world, Input::Manager input)
{
    auto [mouseX, mouseY] = input.GetMousePosition();
    auto view = world.view<Cursor, Transform>();
    for (auto ent: view) {
        auto &transform = view.get<Transform>(ent);
        transform.Translate = {mouseX / TileSize::Size, mouseY / TileSize::Size, 10};
    }
}

void InputSystem::GenerateNewMap(World &world, Dispatcher &dispatcher, Input::Manager input)
{
    Noise &noise = Noise::getInstance();
    if (input.IsActionPressed(Input::ACTION3)) {
        noise.SetRandomSeed();
        dispatcher.Send<ReloadEvent>(ReloadEvent {});
    }
}

void InputSystem::UpdateTile(World &world, Dispatcher &dispatcher, Input::Manager input)
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
