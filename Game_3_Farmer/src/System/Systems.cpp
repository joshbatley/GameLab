#include "Systems.h"

void Systems::Update(entt::registry &reg)
{
    Camera &camera = reg.get<Camera>(reg.view<Camera>().front());
    if(_input.IsActionDown(Input::InputAction::LEFT)) {
        camera.pos.x += camera.pos.x + 1 <= 0 ? 1 : 0;;
    }

    if(_input.IsActionDown(Input::InputAction::RIGHT)) {
        camera.pos.x -= 1;
    }

    if(_input.IsActionDown(Input::InputAction::UP)) {
        camera.pos.y += camera.pos.y + 1 <= 0 ? 1 : 0;
    }

    if(_input.IsActionDown(Input::InputAction::DOWN)) {
        camera.pos.y -= 1;
    }

    if(_input.IsActionDown(Input::InputAction::ACTION1)) {
        camera.scale += camera.scale+1 == 16 ? 0 : 1;
    }

    if(_input.IsActionDown(Input::InputAction::ACTION2)) {
        camera.scale -= camera.scale-1 == 4 ? 0: 1;
    }

}

void Systems::Render(entt::registry &reg, Renderer::Manager &render)
{
    Camera &camera = reg.get<Camera>(reg.view<Camera>().front());
    auto view = reg.view<Tile>();
    view.each([&reg, &render, &camera](auto entity, Tile& tile) {
        Position e = reg.get<Position>(entity);
        SDL_Rect src = { tile.src.x, tile.src.y,tile.Size, tile.Size };
        auto x = (e.Dest.x + camera.pos.x);
        auto y = (e.Dest.y + camera.pos.y);
        SDL_Rect dest = { x * camera.scale, y * camera.scale, camera.scale, camera.scale };
        if (!(x < 0 || x > (80 * camera.scale) || y < 0 || y > (45 * camera.scale))) {
            render.Render(SPRITE_TEXTURE_KEY,src, dest);
        }
    });
}
