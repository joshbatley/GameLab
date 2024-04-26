#include <entt/entt.hpp>
#include "Engine/Engine.h"
#include "Player.h"

int main()
{
    Window::Manager window("Game 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_RESIZABLE);
    Renderer::Manager renderer(window.GetRenderer());

    Input::Manager inputManager;
    entt::registry registry;

    auto ent = registry.create();
    registry.emplace<Player>(ent, 1);
    registry.emplace<Entity>(ent);

    auto ent2 = registry.create();
    registry.emplace<Player>(ent2, 2);
    registry.emplace<Entity>(ent2);

    bool isRunning = true;
    while (isRunning) {
        window.FrameStart();

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
        auto view = registry.view<Entity>();
        for (auto entity : view) {
            auto& player = registry.get<Player>(entity);
            player.Update();
        }

        renderer.SetDrawColor();
        window.Clear();

        // Renders

        window.LimitFrameRate();
        window.Present();
    }
    window.CleanUp();
    renderer.CleanUp();
    return 0;
}