#include "Game.h"
#include <iostream>
#include <string>

SDL_Texture *playerTex;
SDL_Rect src, dest;

Game::Game()
{}
Game::~Game()
{}

void Game::Init(const char *title, int x, int y, int width, int height, bool isFullscreen)
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

    std::string path = "/" + std::string(DUNGEON_STUFF) + "/characters/Archer/archer-idle-front-v2.png";
    SDL_Surface *tmp = IMG_Load(path.c_str());
    playerTex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT
            || event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
                 && event.window.windowID == SDL_GetWindowID(window))
            isRunning = false;
    }
}

void Game::Update()
{
    dest.h = 128;
    dest.w = 128;
    src.w = 24;
    src.h = 24;
}

void Game::Render()
{
    //    SDL_SetRenderDrawColor(renderer, 0, 145, 145, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, playerTex, &src, &dest);

    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}