#pragma once

#include "../Components/Components.h"
#include "../Core/GraphicsHandler.h"
#include "../Engine.h"

class RenderSystem {
public:
    static void System(Engine::World &world, Graphics::Handler &renderer);
};
