#pragma once

#include "../Components/Components.h"
#include "../Engine/Engine.h"
#include "../Events.h"
#include "../Utils/Utils.h"

const std::string CURSOR_TEXTURE_KEY = "cursorMap";

class InputSystem {
public:
    static void Plugin(App *app);

private:
    static void SetupCursor(Engine::World &world, Asset::Manager &asset);
    static void CursorUpdate(Engine::World &world, Input::Manager &input);
    static void GenerateNewMap(Engine::World &world, Dispatcher &dispatcher, Input::Manager &input);
    static void UpdateTile(Engine::World &world, Dispatcher &dispatcher, Input::Manager &input);
};
