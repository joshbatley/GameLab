#include "Engine/Engine.h"
#include "System/Systems.h"
#include "TimeManager.h"
#include "WorldManager.h"

int main()
{
    Window::Manager window("Game 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
    Renderer::Manager renderer(window.GetRenderer());

    renderer.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(HANA_CARAKA) + "/world/tileset/world-summer-tileset.png").c_str());

    Input::Manager input;
    TimeManager timeManager;

    WorldManager worldManager;
    Systems updateSystem(input);

    worldManager.LoadLevel();

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
            worldManager.LoadNewLevel();
        }

        // Updates
        updateSystem.Update(worldManager.GetReg());

        worldManager.LoadLevel();

        // Renders
        renderer.SetDrawColor();
        window.Clear();

        updateSystem.Render(worldManager.GetReg(), renderer);

        window.LimitFrameRate();
        window.Present();
    }

    window.CleanUp();
    renderer.CleanUp();
    return 0;
}