#include "Systems.h"

void Systems::Update(entt::registry &reg)
{

}

void Systems::Render(entt::registry &reg, Renderer::Manager &render)
{
    auto view = reg.view<Tile>();
    view.each([&render](auto entity, Tile& tile) {
        render.Render( SPRITE_TEXTURE_KEY, tile.GetSrcTile(), tile.GetDestTile());
    });
}
