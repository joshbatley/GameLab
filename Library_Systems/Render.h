#pragma once

#include "../Core/Graphics.h"
#include "../Engine.h"

class Render {
public:
    static void System(Engine::World &world, Graphics::Manager &renderer);
};
