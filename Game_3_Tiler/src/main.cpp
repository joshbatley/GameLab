#include "Engine/Engine.h"
#include "Events.h"
#include "System/InputSystem.h"
#include "System/TileSystem.h"

int main()
{
    auto d = GameData {};
    App app(Window::Config {"Game 3 - Tiler"});
    app
      .AddResource(d)
      .AddPlugin(InputSystem::Plugin)
      .AddPlugin(TileSystem::Plugin)
      .Run();
}