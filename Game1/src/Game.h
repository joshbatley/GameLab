#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Player.h"
#include "SDL.h"
#include "SDL_image.h"

class Game
{
  public:
    Game();
    ~Game();
    void Init(const char* title, int x, int y, int width, int height, bool isFullscreen);

    void HandleEvents();
    static void Update();
    void Render() const;
    void Clean() const;

    bool IsRunning() const
    {
        return isRunning;
    };

  private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
};


#endif// GAME_GAME_H
