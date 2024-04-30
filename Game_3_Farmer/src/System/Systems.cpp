#include "UpdateSystem.h"

void UpdateSystem::Update(entt::registry &reg)
{
    auto view = reg.view<RenderedComponent>();
    for (auto entity: view) {
        if (view.get<RenderedComponent>(entity).shouldRender) {
            if (reg.all_of<Player>(entity)) {
                auto player = reg.get<Player>(entity);
                player.Update();
            }
        }
    }
}
