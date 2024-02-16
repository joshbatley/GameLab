#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "SDL.h"
#include "SDL_image.h"

class Game
{
  public:
    Game();
    ~Game();
    void Init(const char *title, int x, int y, int width, int height, bool isFullscreen);

    void HandleEvents();
    void Update();
    void Render();
    void Clean();

    bool IsRunning()
    {
        return isRunning;
    };

  private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};


#endif// GAME_GAME_H
