#include "Render.h"

void Render::System(Engine::World &world, Graphics::Manager &renderer)
{
    auto view = world.view<Sprite, Transform>();
    std::vector<Engine::Entity> entities(view.begin(), view.end());
    std::sort(entities.begin(), entities.end(), [&view](Engine::Entity a, Engine::Entity b) {
        return view.get<Transform>(a).translate.z < view.get<Transform>(b).translate.z;
    });

    for (auto entity: entities) {
        auto transform = view.get<Transform>(entity);
        auto sprite = view.get<Sprite>(entity);

        Vec::ivec4 dest = {
          transform.translate.x * transform.scale.x,
          transform.translate.y * transform.scale.y,
          transform.scale.x, transform.scale.y};

        Vec::ivec4 src = {sprite.src.x, sprite.src.y, sprite.size.x, sprite.size.y};
        renderer.Render(sprite.texture, src, dest);
    }
}