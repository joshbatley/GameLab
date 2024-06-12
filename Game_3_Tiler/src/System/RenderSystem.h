#pragma once

#include "../Components/Components.h"
#include <Engine.h>
#include <algorithm>

class RenderSystem {
public:
    static void Render(World &world, Graphics::Manager &renderer);
};
