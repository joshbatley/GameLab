#pragma once

#include "InputManager.h"
#include <SDL.h>


class Player {
    static constexpr int MOVE_AMOUNT = 32;

public:
    Player(std::string textureUp, std::string textureDown, std::string textureLeft, std::string textureRight, Input::Manager &inputManager);
    std::pair<int, int> Update(int level[15][15]);
    std::tuple<SDL_Rect, SDL_Rect, std::string> Render();

private:
    Uint32 _startTicks = SDL_GetTicks();
    SDL_Rect _src;
    SDL_Rect _dest;
    std::string _textureDown;
    std::string _textureUp;
    std::string _textureLeft;
    std::string _textureRight;
    std::string _texture;
    Input::Manager &_inputManager;
};
