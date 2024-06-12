#include "Render.h"

void Render::System(Engine::World &world, Graphics::Manager &renderer)
{
    auto view = world.view<Sprite, Transform>();
    std::vector<Engine::Entity> entities(view.begin(), view.end());
    std::sort(entities.begin(), entities.end(), [&view](Engine::Entity a, Engine::Entity b) {
        return view.get<Transform>(a).Translate.z < view.get<Transform>(b).Translate.z;
    });

    for (auto entity: entities) {
        auto transform = view.get<Transform>(entity);
        auto sprite = view.get<Sprite>(entity);

        Vec::ivec4 dest = {
          transform.Translate.x * transform.Scale.x,
          transform.Translate.y * transform.Scale.y,
          transform.Scale.x, transform.Scale.y};

        Vec::ivec4 src = {sprite.Src.x, sprite.Src.y, sprite.Size.x, sprite.Size.y};
        renderer.Render(sprite.Texture, src, dest);
    }
}