#include "Systems.h"

void Systems::Update(entt::registry &reg)
{
    Camera &camera = reg.get<Camera>(reg.view<Camera>().front());
    if (_input.IsActionDown(Input::InputAction::LEFT)) {
        camera.pos.x -= 1 * camera.speed;
    }

    if (_input.IsActionDown(Input::InputAction::RIGHT)) {
        camera.pos.x += 1 * camera.speed;
    }

    if (_input.IsActionDown(Input::InputAction::UP)) {
        camera.pos.y -= 1 * camera.speed;
    }

    if (_input.IsActionDown(Input::InputAction::DOWN)) {
        camera.pos.y += 1 * camera.speed;
    }

    if (_input.IsActionDown(Input::InputAction::ACTION1)) {
        if (camera.scale + 1 <= 16) {
            camera.scale += 2;
            camera.pos.x -= 8;
            camera.pos.y -= 8;
        }
    }

    if (_input.IsActionDown(Input::InputAction::ACTION2)) {
        if (camera.scale - 1 > 1) {
            camera.scale -= 2;
            camera.pos.x += 8;
            camera.pos.y += 8;
        }
    }
}

void Systems::Render(entt::registry &reg, Renderer::Manager &render)
{
    Camera &camera = reg.get<Camera>(reg.view<Camera>().front());
    auto view = reg.view<Tile>();
    view.each([&reg, &render, &camera](auto entity, Tile &tile) {
        Position e = reg.get<Position>(entity);

        SDL_Rect dest = {
          (e.Dest.x + camera.pos.x) * camera.scale,
          (e.Dest.y + camera.pos.y) * camera.scale,
          camera.scale,
          camera.scale};

        if (camera.scale < 4) {
            switch (tile.type) {
                case Water:
                    render.RenderColor({ 0,0,255,0 }, dest);
                    break;
                case Land:
                    render.RenderColor({ 255,0,0,0 }, dest);
                    break;
                case Sand:
                    render.RenderColor({ 255,255,0,0 }, dest);
                    break;
                default:
                    render.RenderColor({ 255,0,0,0 }, dest);
                    break;
            }
        } else {
            SDL_Rect src = {tile.src.x, tile.src.y, tile.Size, tile.Size};
            render.Render(SPRITE_TEXTURE_KEY, src, dest);
        }
    });
}
