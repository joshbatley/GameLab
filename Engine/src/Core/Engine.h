#pragma once

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <entt/entt.hpp>

namespace Engine {
    using World = entt::registry;
    using Entity = entt::entity;

    using Texture = SDL_Texture *;
    using Font = TTF_Font *;

    template<typename ResourceType>
    struct Resource {
        ResourceType &data;
        ResourceType &into()
        {
            return data;
        }
    };
}