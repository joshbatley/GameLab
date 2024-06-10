#include "RenderSystem.h"

void RenderSystem::Setup(entt::registry &reg, Asset::Manager manager)
{
    auto ent = reg.create();
    auto &cursor = reg.emplace<Cursor>(ent);
    reg.emplace<RenderedComponent>(ent);
    cursor.texture = manager.LoadTexture(CURSOR_TEXTURE_KEY, (std::string(SPROUT_LANDS) + "/ui/icons/select.png").c_str());
}

void RenderSystem::Render(entt::registry &reg, Renderer::Manager &renderer)
{
    auto view = reg.view<Cursor>();
    for (auto entity: view) {
        auto cursor = reg.get<Cursor>(entity);
        float x = cursor.Pos.x * TileSize::Size;
        float y = cursor.Pos.y * TileSize::Size;
        auto dest = Engine::ivec4 {(int)x, int(y), TileSize::Size, TileSize::Size};
        auto src = Engine::ivec4 {0, 0, 32, 32};
        renderer.Render(cursor.texture, src, dest);
    }
}
