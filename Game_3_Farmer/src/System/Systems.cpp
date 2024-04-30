#include "Systems.h"

void Systems::Update(entt::registry &reg)
{

}

void Systems::Render(entt::registry &reg)
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
