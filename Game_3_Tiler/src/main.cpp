#include "App.h"

#include "Engine/Engine.h"
#include "System/InputSystem.h"
#include "System/RenderSystem.h"
#include "System/TileSystem.h"


int main()
{
    App app("Game 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, SDL_WINDOW_RESIZABLE);
    app
      .AddSystem(SETUP, TileSystem::Setup)
      .AddSystem(SETUP, RenderSystem::Setup)
      .AddSystem(RENDER, TileSystem::Render)
      .AddSystem(RENDER, RenderSystem::Render)
      .AddEvent<ReloadEvent>(TileSystem::ReloadWorld)
      .AddEvent<UpdateTileEvent>(TileSystem::UpdateTile)
      .AddPlugin(InputSystem::Plugin)
      .Run();
}