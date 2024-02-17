#include "Game.h"
#include <string>

Player* player;


Game::Game()
{}

Game::~Game()
{}

void Game::Init(const char* title, int x, int y, int width, int height, bool isFullscreen)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Error creating SDL_Renderer!");
        return;
    }

    isRunning = true;
    player = new Player(renderer);
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
        }
    }
}

void Game::Update()
{
    player->Update();
}

void Game::Render() const
{
    SDL_SetRenderDrawColor(renderer, 0, 145, 145, 255);
    SDL_RenderClear(renderer);

    player->Render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Clean() const
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}