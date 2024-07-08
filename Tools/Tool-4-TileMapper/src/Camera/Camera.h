#pragma once

#include "Components/Components.h"
#include "Core/Engine.h"
#include "Core/GraphicsHandler.h"
#include "Utils/AppSettings.h"
#include <glm/common.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct ViewPort {
    glm::ivec2 position {};
    glm::ivec2 size {};
};

struct RenderLayer {
    int layer;
};

struct Box {
    glm::ivec4 color;
    bool filled = false;
};

// struct Image {
// };

struct VisibleEntities {
    std::vector<Engine::Entity> entities;
};

struct Cursor {
};
struct Camera {
    bool active = true;
    ViewPort viewport;

    glm::ivec2 viewportToWorldSpace(glm::ivec2 local)
    {

        auto newX = glm::clamp(local.x, this->viewport.position.x, this->viewport.position.x + this->viewport.size.x) - this->viewport.position.x;
        auto newY = glm::clamp(local.y, this->viewport.position.y, this->viewport.position.y + this->viewport.size.y) - this->viewport.position.y;

        return {newX, newY};
    }

    glm::ivec2 worldspaceToViewPort(glm::ivec3 transform, glm::ivec3 local)
    {
        auto newX = local.x + transform.x + this->viewport.position.x;
        auto newY = local.y + transform.y + this->viewport.position.y;

        return {newX, newY};
    }

    glm::imat4x2 cameraPoints(Transform transform)
    {
        auto camX = viewport.position.x + transform.position.x;
        auto camY = viewport.position.y + transform.position.y;

        return glm::imat4x2 {
          {camX, camY},                                    // top left
          {camX + viewport.size.x, camY},                  // top right
          {camX + viewport.size.x, camY + viewport.size.y},// bottom right
          {camX, camY + viewport.size.y}                   // bottom left
        };
    }
};

struct CameraBundle {
    Camera camera;
    ViewPort viewport;
    Transform transform;

    void Create(Engine::World &world)
    {
        const auto camera = world.create();
        world.emplace<Camera>(camera, true, this->viewport);
        world.emplace<Transform>(camera, this->transform);
        world.emplace<VisibleEntities>(camera);
    }
};

void GetVisibleEntities(Engine::World &world, Graphics::Handler &graphics);
void RenderSprites(Engine::World &world, Graphics::Handler &graphics);
void RenderGizmos(Engine::World &world, Graphics::Handler &graphics);

// enum VisibilityState {
//     Hidden,
//     Visible,
// };
//
// struct Visibility {
//     VisibilityState state;
// };

// transform 0,0
// viewport 0,0
// ent global 0,0

// transform 0,0
// viewport 100, 0
// ent global 100, 0

// transform 100,0
// viewport 0,0
// ent global