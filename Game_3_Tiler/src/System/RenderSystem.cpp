#include "RenderSystem.h"

void RenderSystem::Render(entt::registry &reg, Renderer::Manager &renderer)
{
    auto view = reg.view<RenderedComponent>();
    for (auto entity: view) {
        auto comp = view.get<RenderedComponent>(entity);
        auto cursor = reg.get<Cursor>(entity);
        if (comp.shouldRender) {
            float x = cursor.Pos.x * TileSize::Size;
            float y = cursor.Pos.y * TileSize::Size;
            auto dest = Engine::ivec4 {(int)x, int(y), TileSize::Size, TileSize::Size};
            auto src = Engine::ivec4 {0, 0, 32, 32};
            renderer.Render(CURSOR_TEXTURE_KEY, src, dest);
        }
    }
}
