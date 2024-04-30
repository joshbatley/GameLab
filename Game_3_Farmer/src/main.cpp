#include "Engine/Engine.h"
#include "System/Systems.h"
#include "TimeManager.h"
#include "WorldManager.h"
#include <entt/entt.hpp>

int main()
{
    Window::Manager window("Game 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_RESIZABLE);
    Renderer::Manager renderer(window.GetRenderer());

    entt::registry registry;

    Input::Manager inputManager;
    TimeManager timeManager;

    WorldManager worldManager;
    Systems updateSystem;

    worldManager.Init(registry);

    bool isRunning = true;
    while (isRunning) {
        window.FrameStart();
        timeManager.Update(SDL_GetTicks());
        inputManager.Update();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
            inputManager.ProcessEvents(&event);
        }

        // Updates
        updateSystem.Update(registry);

        renderer.SetDrawColor();
        window.Clear();

        // Renders
        updateSystem.Render(registry);

        window.LimitFrameRate();
        window.Present();
    }

    window.CleanUp();
    renderer.CleanUp();
    return 0;
}