#pragma once

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
    explicit InputSystem(Input::Manager &input)
        : _input(input) {}
    void Update(entt::registry &reg, entt::dispatcher &dispatcher);

private:
    Input::Manager &_input;
};
