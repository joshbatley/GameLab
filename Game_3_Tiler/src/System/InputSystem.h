#pragma once

#include "../Components/Components.h"
#include "../Events.h"
#include "../Utils/Utils.h"
#include <Engine.h>

class InputSystem {
public:
    static void Plugin(App *app);

private:
    static void SetupCursor(World &world, Asset::Manager asset);
    static void CursorUpdate(World &world, Input::Manager input);
    static void GenerateNewMap(World &world, Dispatcher &dispatcher, Input::Manager input);
    static void UpdateTile(World &world, Dispatcher &dispatcher, Input::Manager input);
};
