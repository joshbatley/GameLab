#include "Player.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Tile.h"
#include <iostream>

const auto FPS = 60;
const auto FrameDelay = 1000 / FPS;

int main(int, char**)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cout << "SDL failed to init. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto window =
      SDL_CreateWindow("Game 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_ShowCursor(SDL_DISABLE);

    Player* player = new Player(renderer, 1);
    Tile* tile = new Tile(renderer);
    bool isRunning = true;
    int level = 1;

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("assets/font.ttf", 20);

    while (isRunning) {
        Uint32 frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONUP:
                if (level == 4) {
                    isRunning = false;
                }
                break;
            case SDL_KEYDOWN:
                if (level == 4) {
                    isRunning = false;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    auto pos = player->MoveRight(tile->Level);
                    auto completed = tile->removeCoin(pos.first, pos.second);
                    if (completed) {
                        level++;
                        tile->loadLevel(level);
                    }
                }
                if (event.key.keysym.sym == SDLK_a) {
                    auto pos = player->MoveLeft(tile->Level);
                    auto completed = tile->removeCoin(pos.first, pos.second);
                    if (completed) {
                        level++;
                        tile->loadLevel(level);
                    }
                }
                if (event.key.keysym.sym == SDLK_w) {
                    auto pos = player->MoveUp(tile->Level);
                    auto completed = tile->removeCoin(pos.first, pos.second);
                    if (completed) {
                        level++;
                        tile->loadLevel(level);
                    }
                }
                if (event.key.keysym.sym == SDLK_s) {
                    auto pos = player->MoveDown(tile->Level);
                    auto completed = tile->removeCoin(pos.first, pos.second);
                    if (completed) {
                        level++;
                        tile->loadLevel(level);
                    }
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (level >= 4) {
            SDL_Color textColor = { 255, 255, 255 };
            std::string text = "Game Over";

            // Render text to a surface
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), textColor);

            // Convert surface to texture
            SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_Rect messageRect = { 180, 200, surfaceMessage->w, surfaceMessage->h };
            SDL_RenderCopy(renderer, message, NULL, &messageRect);
        } else {
            player->Update();


            tile->render(renderer);
            player->Render(renderer);

            // Set text and color
            SDL_Color textColor = { 255, 255, 255 };
            std::string text = "Coins Left: " + std::to_string(tile->GetCoinsLeft());

            // Render text to a surface
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), textColor);

            // Convert surface to texture
            SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
            SDL_Rect messageRect = { 10, 450, surfaceMessage->w, surfaceMessage->h };

            SDL_RenderCopy(renderer, message, NULL, &messageRect);
        }

        int frameTime = SDL_GetTicks() - frameStart;
        if (FrameDelay > frameTime) {
            SDL_Delay(FrameDelay - frameTime);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    return 0;
}