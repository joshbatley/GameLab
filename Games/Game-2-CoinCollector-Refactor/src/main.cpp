#include "InputManager.h"
#include "Player.h"
#include "Renderer.h"
#include "Tile.h"
#include "WindowManager.h"

std::string FONT_PATH = (std::string(FONTS) + "/monogram/monogram.ttf");
const char *FONT_NAME = "Monogram";

// MOVE These into classes one for the name game.
std::string SPRITE_TEXTURE_KEY = "spriteMap";
std::string COIN_TEXTURE_KEY = "textureCoin";
std::string PLAYER_UP = "playerUp";
std::string PLAYER_DOWN = "playerDown";
std::string PLAYER_LEFT = "playerLeft";
std::string PLAYER_RIGHT = "playerRight";

Window::Manager window("Game 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_RESIZABLE);
Renderer::Manager renderer(window.GetRenderer());

void Init()
{
    renderer.LoadTexture(PLAYER_DOWN, (std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-front.png").c_str());
    renderer.LoadTexture(PLAYER_UP, (std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-back.png").c_str());
    renderer.LoadTexture(PLAYER_LEFT, (std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-left.png").c_str());
    renderer.LoadTexture(PLAYER_RIGHT, (std::string(DUNGEON_STUFF) + "/characters/archer/archer-idle-right.png").c_str());

    renderer.LoadTexture(SPRITE_TEXTURE_KEY, (std::string(DUNGEON_STUFF) + "/tiles/dungeon-tiles.png").c_str());
    renderer.LoadTexture(COIN_TEXTURE_KEY, (std::string(DUNGEON_STUFF) + "/objects/coins.png").c_str());

    renderer.LoadFont(FONT_NAME, FONT_PATH.c_str(), 50);
}

int main()
{
    Init();
    Input::Manager inputManager;
    Tile tile(SPRITE_TEXTURE_KEY, COIN_TEXTURE_KEY);
    Player player(PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT, inputManager);

    int level = 1;
    tile.LoadLevel(level);

    bool isRunning = true;
    while (isRunning) {
        window.FrameStart();

        inputManager.Update();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
            inputManager.ProcessEvents(&event);
        }

        auto l = tile.GetLevel();
        auto [x,y] = player.Update(*l);
        tile.RemoveCoin(x / 32, y / 32);

        renderer.SetDrawColor();
        window.Clear();

        if (level >= 4) {
            SDL_Color textColor = {255, 255, 255};
            auto text = "Game Over";
            SDL_Rect dest = {160, 200, 0, 0};
            renderer.RenderText(text, FONT_NAME, textColor, dest);

        } else {
            for (auto [src2, dest2, tex2]: tile.Render()) {
                renderer.Render(tex2, src2, dest2);
            }
            auto [src, dest, tex] = player.Render();
            renderer.Render(tex, src, dest);

            SDL_Color textColor = {255, 255, 255};
            std::string text = "Coins Left: " + std::to_string(tile.GetCoinsLeft());
            SDL_Rect messageDest = {10, 440, 0, 0};
            renderer.RenderText(text.c_str(), FONT_NAME, textColor, messageDest);
        }

        if (tile.GetCoinsLeft() == 0) {
            level++;
            tile.LoadLevel(level);
        }

        window.LimitFrameRate();
        window.Present();
    }
    window.CleanUp();
    renderer.CleanUp();
    return 0;
}
