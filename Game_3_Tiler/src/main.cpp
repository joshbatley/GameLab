#include "Engine/Engine.h"
#include "System/InputSystem.h"
#include "System/RenderSystem.h"
#include "System/TileSystem.h"
#include "TimeManager.h"
#include <entt/entt.hpp>

int main()
{
    Window::Manager window("Game 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, SDL_WINDOW_RESIZABLE);
    Renderer::Manager renderer(window.GetRenderer());

    renderer.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());
    renderer.LoadTexture(CURSOR_TEXTURE_KEY, (std::string(SPROUT_LANDS) + "/ui/icons/select.png").c_str());

    Input::Manager input;
    TimeManager timeManager;
    TileSystem tileSystem;
    InputSystem inputSystems(input);
    RenderSystem renderSystem;

    entt::registry reg;
    entt::dispatcher dispatcher;

    auto ent = reg.create();
    reg.emplace<Cursor>(ent);
    reg.emplace<RenderedComponent>(ent);

    tileSystem.Setup(reg);

    bool isRunning = true;
    while (isRunning) {
        window.FrameStart();
        timeManager.Update(SDL_GetTicks());
        input.Update();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
            input.ProcessEvents(&event);
        }

        if (input.IsActionPressed(Input::ACTION3)) {
            tileSystem.Update(reg);
        }

        inputSystems.Update(reg, dispatcher);

        renderer.SetDrawColor();
        window.Clear();

        tileSystem.Render(reg, renderer);
        renderSystem.Render(reg, renderer);

        window.LimitFrameRate();
        window.Present();
    }

    window.CleanUp();
    renderer.CleanUp();
    return 0;
}