#include "WorldManager.h"

WorldManager::WorldManager()
{
}

void WorldManager::Init(entt::registry &reg)
{
    auto ent = reg.create();
    reg.emplace<Player>(ent, 1);
    reg.emplace<RenderedComponent>(ent);
}
