#pragma once

#include "../App.h"
#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "../Utils/Utils.h"
#include <entt/entt.hpp>

struct MouseEvent {
    int x;
    int y;
};

struct ReloadEvent {
    int id;
};

class InputSystem {
public:
    static void Plugin(App *app);
};
