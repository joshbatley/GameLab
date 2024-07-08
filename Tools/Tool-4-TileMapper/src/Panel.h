#pragma once

#include "Core/Engine.h"
#include "Core/EventHandler.h"
#include "Core/Resource.h"

#include <glm/vec2.hpp>
#include <imgui.h>

struct UpdateBoxSize {
    glm::vec2 size;
    glm::vec2 pos;
};

struct Data {
    glm::ivec2 size = {128, 128};
    glm::ivec2 pos = {128, 128};
};

void SetupPanel(Engine::World &_, Event::Handler &eventHandler, Engine::Resource<Data> data);