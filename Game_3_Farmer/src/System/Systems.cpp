#include "Systems.h"

void Systems::Update(entt::registry &reg)
{

}

void Systems::Render(entt::registry &reg, Renderer::Manager &render)
{
    auto view = reg.view<Tile>();
    view.each([&reg, &render](auto entity, Tile& tile) {
        Position e = reg.get<Position>(entity);
        render.Render(SPRITE_TEXTURE_KEY,
                      { tile.src.x,tile.src.y,tile.Size, tile.Size  },
                      { e.Dest.x * 8, e.Dest.y * 8, 8, 8 });
    });
}
