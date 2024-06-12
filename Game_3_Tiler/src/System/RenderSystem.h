#pragma once

#include "../App.h"
#include "../AssetManager.h"
#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include <algorithm>

class RenderSystem {
public:
    static void Render(World &world, Renderer::Manager &renderer);
};
