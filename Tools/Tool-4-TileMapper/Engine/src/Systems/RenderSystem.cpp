#include "RenderSystem.h"

void RenderSystem::System(Engine::World &world, Graphics::Handler &renderer)
{
    auto view = world.view<Sprite, Transform>();
    std::vector<Engine::Entity> entities(view.begin(), view.end());
    std::ranges::sort(entities, [&view](const Engine::Entity a, const Engine::Entity b) {
        return view.get<Transform>(a).position.z < view.get<Transform>(b).position.z;
    });

    for (auto entity: entities) {
        auto transform = view.get<Transform>(entity);
        auto sprite = view.get<Sprite>(entity);

        glm::ivec4 dest = {
          transform.position.x,
          transform.position.y,
          transform.scale.x, transform.scale.y};

        // glm::ivec4 src = {sprite.src.x, sprite.src.y, sprite.size.x, sprite.size.y};
        // renderer.Render(sprite.texture, src, dest);
    }
}