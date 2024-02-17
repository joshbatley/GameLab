#include "Player.h"

Player::Player(SDL_Renderer* renderer)
{
    texture = Utils::LoadTex(renderer, path.c_str());
}

void Player::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

int count = 0;
int skin = 0;

void Player::Update()
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
}
