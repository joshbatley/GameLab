#include "App.h"

#include "Engine/Engine.h"
#include "Events.h"
#include "System/InputSystem.h"
#include "System/RenderSystem.h"
#include "System/TileSystem.h"


int main()
{
    App app("Game 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, SDL_WINDOW_RESIZABLE);
    app
      .AddPlugin(TileSystem::Plugin)
      .AddPlugin(InputSystem::Plugin)
      .AddSystem(RENDER, RenderSystem::Render)
      .Run();
}