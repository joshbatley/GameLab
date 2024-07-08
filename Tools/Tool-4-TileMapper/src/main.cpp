#include "Camera/Camera.h"
#include "Engine.h"
#include "Panel.h"

#include <glm/glm.hpp>
#include <iostream>

void SetUpCamera(Engine::World &world)
{
    auto [width, height] = AppSettings::GetInstance().WindowSize();
    CameraBundle {
      {},
      {{400, 0}, {width - 400, height}},
      {}}
      .Create(world);
}

void RenderLines(Engine::World &world, UpdateBoxSize ev)
{
    world.clear<Line>();
    auto maxX = round(ev.size.x / 32) + 1;
    auto maxY = round(ev.size.y / 32) + 1;
    auto posX = ev.pos.x;
    auto posY = ev.pos.y;


    for (int x = 0; x < maxX; ++x) {
        auto e = world.create();
        world.emplace<Line>(e, glm::ivec2 {(x * 32) + posX, posY}, glm::ivec2 {(x * 32) + posX, ev.pos.y + ev.size.y}, glm::ivec4 {255, 255, 255, 255});
    }

    for (int y = 0; y < maxY; ++y) {
        auto e = world.create();
        world.emplace<Line>(e, glm::ivec2 {posX, (y * 32) + posY}, glm::ivec2 {ev.pos.x + ev.size.x, (y * 32) + posY}, glm::ivec4 {255, 255, 255, 255});
    }
}

void setupCursorSquare(Engine::World &world)
{
    auto e = world.create();
    world.emplace<Sprite>(e, glm::ivec4 {255, 0, 0, 255});
    world.emplace<Transform>(e, glm::ivec3 {0, 0, 0}, glm::ivec3 {33, 33, 0});
    world.emplace<Cursor>(e);
}

void UpdateCursor(Engine::World &world, Input::Manager &input)
{
    auto cameras = world.view<Camera>();
    for (auto e: cameras) {
        auto camera = world.get<Camera>(e);
        auto [x, y] = input.GetMousePosition();
        auto mouseLocal = camera.viewportToWorldSpace({x, y});
        mouseLocal.x = glm::round(mouseLocal.x / 32) * 32;
        mouseLocal.y = glm::round(mouseLocal.y / 32) * 32;

        auto view = world.view<Box, Transform, Cursor>();
        for (auto ent: view) {
            auto &box = view.get<Transform>(ent);
            box.position = {mouseLocal.x, mouseLocal.y, 0};
        }
    }
}

void SetupImage(Engine::World &world, Event::Handler &eventHandler, Asset::Handler &asset)
{
    auto texture = asset.LoadTexture((std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());

    auto ent = world.create();
    world.emplace<Sprite>(ent, Sprite {.size {128, 128}, .color = {0, 255, 0, 255}, .srcSize = {0, 0, 48, 48}});
    world.emplace<Transform>(ent, glm::ivec3 {0, 0, 0});
    world.emplace<GlobalTransform>(ent);
    world.emplace<Image>(ent, Image {texture});
    // eventHandler.Send<UpdateBoxSize>({{128, 128}, {128, 128}});
}

void UpdatedImage(Engine::World &world, UpdateBoxSize ev)
{
    auto view = world.view<Image, Transform>();
    for (auto e: view) {
        auto &transform = world.get<Transform>(e);
        transform.scale = {ev.size.x, ev.size.y, 0};
        transform.position = {ev.pos.x, ev.pos.y, 0};
    }
}

void MoveBox(Engine::World &world, Input::Manager &input)
{
    auto view = world.view<Sprite, Transform>();
    for (auto ent: view) {
        auto &transform = world.get<Transform>(ent);
        if (input.IsActionPressed(Input::UP)) {
            transform.position.y -= 32;
        }
        if (input.IsActionPressed(Input::DOWN)) {
            transform.position.y += 32;
        }
        if (input.IsActionPressed(Input::LEFT)) {
            transform.position.x -= 32;
        }
        if (input.IsActionPressed(Input::RIGHT)) {
            transform.position.x += 32;
        }
    }
}

void UpdatedGlobalTransform(Engine::World &world)
{
    auto cameras = world.view<Camera, Transform>();
    auto transforms = world.view<Transform, GlobalTransform>();
    for (auto [_, camera, cameraTransform]: cameras.each()) {
        for (auto [_, transform, global]: transforms.each()) {
            auto transformLocal = camera.worldspaceToViewPort(cameraTransform.position, transform.position);
            global.position = {transformLocal.x, transformLocal.y, transform.position.z};
        }
    }
}

int main()
{
    App app(Window::Config {
      .title = "Tool TileMapper",
      .showCursor = false,
      .relativeMouse = false,
    });

    app
      .AddResource<Data>()
      .AddSystem(System::UPDATE, SetupPanel)
      .AddSystem(System::SETUP, SetUpCamera)
      .AddSystem(System::SETUP, SetupImage)
      .AddSystem(System::SETUP, setupCursorSquare)
      .AddSystem(System::UPDATE, UpdateCursor)
      .AddSystem(System::UPDATE, MoveBox)
      .AddSystem(UpdatedImage)
      .AddSystem(RenderLines)
      .AddSystem(System::RENDER, UpdatedGlobalTransform)
      .AddSystem(System::RENDER, GetVisibleEntities)
      .AddSystem(System::RENDER, RenderSprites)
      .AddSystem(System::RENDER, RenderGizmos)
      .Run();
}
