#include "Game.h"
#include <iostream>

int main(int, char**)
{
    Game* game = new Game();
    const auto FPS = 60;
    const auto FrameDelay = 1000 / FPS;
    Uint32 frameStart;
    const std::string myPath = DUNGEON_STUFF;

    game->Init("Game 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

    while (game->IsRunning()) {
        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        int frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime) {
            SDL_Delay(FrameDelay - frameTime);
        }
    }

    game->Clean();
    return 0;
}