#pragma once
#include <glm/vec3.hpp>

struct Transform {
    glm::ivec3 position {0, 0, 0};
    glm::ivec3 scale {1, 1, 1};
    glm::ivec3 rotation {0, 0, 0};
};

struct GlobalTransform {
    glm::ivec3 position {0, 0, 0};
    glm::ivec3 scale {1, 1, 1};
    glm::ivec3 rotation {0, 0, 0};
};