#pragma once

#include "Components/Components.h"
#include "Core/GraphicsHandler.h"
#include "Core/Engine.h"

class RenderSystem {
public:
    static void System(Engine::World &world, Graphics::Handler &renderer);
};
