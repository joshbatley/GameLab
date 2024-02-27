#include "Player.h"
#include "SDL.h"
#include "Tile.h"

const auto FPS = 60;
const auto FrameDelay = 1000 / FPS;

int main(int, char**)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    auto window =
      SDL_CreateWindow("Game 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Error creating SDL_Renderer!");
        return -1;
    }

    Player* player = new Player(renderer, 4);
    Tile* tile = new Tile(renderer);
    bool isRunning = true;

    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_1) {
                    tile->loadLevel(1);
                }
                if (event.key.keysym.sym == SDLK_2) {
                    tile->loadLevel(2);
                }
                if (event.key.keysym.sym == SDLK_3) {
                    tile->loadLevel(3);
                }

                if (event.key.keysym.sym == SDLK_d) {
                    player->MoveRight(tile->Level);
                }
                if (event.key.keysym.sym == SDLK_a) {
                    player->MoveLeft(tile->Level);
                }
                if (event.key.keysym.sym == SDLK_w) {
                    player->MoveUp(tile->Level);
                }
                if (event.key.keysym.sym == SDLK_s) {
                    player->MoveDown(tile->Level);
                }
                break;
            }
        }

        player->Update();


        SDL_SetRenderDrawColor(renderer, 0, 145, 145, 255);
        SDL_RenderClear(renderer);

        tile->render(renderer);
        player->Render(renderer);
        SDL_RenderPresent(renderer);

        int frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime) {
            SDL_Delay(FrameDelay - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}