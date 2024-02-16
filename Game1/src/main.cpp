#include "Game.h"
#include <iostream>


int main(int, char **)
{
    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 frameStart;
    auto game = Game();
    const std::string myPath = DUNGEON_STUFF;

    game.Init("Game 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

    while (game.IsRunning()) {

        frameStart = SDL_GetTicks();

        game.HandleEvents();
        game.Update();
        game.Render();

        int frameTime = SDL_GetTicks() - frameStart;
        if (frameStart > frameTime) {
            SDL_Delay(FrameDelay - frameTime);
        }
    }

    game.Clean();
    return 0;
}