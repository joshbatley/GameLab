#pragma once

#include "InputManager.h"
#include <SDL.h>


class Player {
    static constexpr int MOVE_AMOUNT = 32;

public:
    Player(SDL_Texture *textureUp, SDL_Texture *textureDown, SDL_Texture *textureLeft, SDL_Texture *textureRight, Input::Manager &inputManager);
    void Update();
    std::tuple<SDL_Rect, SDL_Rect, SDL_Texture *> Render();

private:
    static bool HandleMovementPause();
    Uint32 _startTicks = SDL_GetTicks();
    SDL_Rect _src;
    SDL_Rect _dest;
    SDL_Texture *_textureDown;
    SDL_Texture *_textureUp;
    SDL_Texture *_textureLeft;
    SDL_Texture *_textureRight;
    SDL_Texture *_texture;
    Input::Manager &_inputManager;
};
