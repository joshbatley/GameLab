#include "Engine.h"
#include "Events.h"
#include "System/InputSystem.h"
#include "System/TileSystem.h"

int main()
{
    App app(Window::Config {"Game 3 - Tiler"});
    app
      .AddResource(GameData {})
      .AddPlugin(InputSystem::Plugin)
      .AddPlugin(TileSystem::Plugin)
      .Run();
}