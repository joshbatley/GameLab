#include "RenderSystem.h"

void RenderSystem::Render(World &world, Renderer::Manager &renderer)
{
    auto view = world.view<Sprite, Transform>();
    std::vector<Entity> entities(view.begin(), view.end());
    std::sort(entities.begin(), entities.end(), [&view](Entity a, Entity b) {
        return view.get<Transform>(a).Translate.z < view.get<Transform>(b).Translate.z;
    });

    for (auto entity: entities) {
        auto transform = view.get<Transform>(entity);
        auto sprite = view.get<Sprite>(entity);

        Engine::ivec4 dest = {
          transform.Translate.x * TileSize::Size,
          transform.Translate.y * TileSize::Size,
          TileSize::Size, TileSize::Size};

        Engine::ivec4 src = {sprite.Src.x, sprite.Src.y, sprite.Size.x, sprite.Size.y};
        renderer.Render(sprite.Texture, src, dest);
    }
}
