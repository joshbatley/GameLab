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

    std::string path = "/" + std::string(SPROUT_LANDS) + "/Characters/character-spritesheet.png";
    SDL_Surface *tmp = IMG_Load(path.c_str());
    playerTex = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
}

void Game::HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

int count = 0;
int skin = 0;

void Game::Update()
{
    count++;
    if (count > 10) {
        count = 0;
        skin++;
        if (skin >= 4) {
            skin = 0;
        }
    }

    dest.h = 128;
    dest.w = 128;
    dest.y = 30;

    src.w = 48;
    src.h = 48;

    src.y = 0;
    src.x = skin * 48;

    //    printf("this");
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