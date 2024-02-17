#include "Game.h"
#include <iostream>

Game *game = new Game();
int main(int, char **)
{
    const int FPS = 60;
    const int FrameDelay = 1000 / FPS;
    Uint32 frameStart;
    const std::string myPath = DUNGEON_STUFF;

    game->Init("Game 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);

    while (game->IsRunning()) {


        frameStart = SDL_GetTicks();
        std::cout << game->IsRunning() << std::endl;

        game->HandleEvents();
        game->Update();
        game->Render();

        int frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime) {
            SDL_Delay(FrameDelay - frameTime);
        }
    }

    std::cout << "Here" << std::endl;
    game->Clean();
    return 0;
}