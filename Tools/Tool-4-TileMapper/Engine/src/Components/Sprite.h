#pragma once

#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct Sprite {
    glm::ivec2 size {};
    glm::ivec4 color {};
    glm::ivec4 srcSize {};

    glm::imat4x2 getAbsPoints(Transform transform)
    {
        auto sX = transform.position.x;
        auto sY = transform.position.y;
        return glm::imat4x2 {
          {sX, sY},                  // topLeft
          {sX + size.x, sY},         // topRight
          {sX + size.x, sY + size.y},//bottomRight
          {sX, sY + size.y}          // bottomLeft
        };
    }
};

struct Image {
    Engine::Texture texture {};
};

// Gizmo
struct Line {
    glm::ivec2 start;
    glm::ivec2 end;
    glm::ivec4 color;
};

struct Rectangle {
    std::array<glm::ivec2, 4> points;
};