#include "Player.h"


const int move_amount = 32;

Player::Player(SDL_Renderer* renderer, int start)
{
    texture = textureDown = Utils::LoadTex(renderer, pathDown.c_str());
    textureUp = Utils::LoadTex(renderer, pathUp.c_str());
    textureLeft = Utils::LoadTex(renderer, pathLeft.c_str());
    textureRight = Utils::LoadTex(renderer, pathRight.c_str());
    dest.h = dest.w = 32;
    dest.y = dest.x = start * 32;

    src.w = src.h = 24;
    src.y = src.x = 0;
}

Player::~Player()
{}

void Player::Render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

std::pair<int, int> Player::MoveRight(std::vector<std::vector<int>>* level)
{
    auto moveX = (dest.x + move_amount) / 32;
    auto moveY = (dest.y) / 32;
    if (level->at(moveY).at(moveX) == 48) {
        dest.x += dest.x + move_amount < 480 ? move_amount : 0;
    }
    texture = textureRight;
    return { moveY, moveX };
}

std::pair<int, int> Player::MoveLeft(std::vector<std::vector<int>>* level)
{
    auto moveX = (dest.x - move_amount) / 32;
    auto moveY = (dest.y) / 32;
    if (level->at(moveY).at(moveX) == 48) {
        dest.x -= dest.x > 0 ? move_amount : 0;
    }
    texture = textureLeft;
    return { moveY, moveX };
}

std::pair<int, int> Player::MoveDown(std::vector<std::vector<int>>* level)
{
    auto moveX = (dest.x) / 32;
    auto moveY = (dest.y + move_amount) / 32;
    if (level->at(moveY).at(moveX) == 48) {
        dest.y += dest.y + move_amount < 480 ? move_amount : 0;
        std::cout << "moving" << std::endl;
    }
    texture = textureDown;
    return { moveY, moveX };
}

std::pair<int, int> Player::MoveUp(std::vector<std::vector<int>>* level)
{
    auto moveX = (dest.x) / 32;
    auto moveY = (dest.y - move_amount) / 32;
    if (level->at(moveY).at(moveX) == 48) {
        dest.y -= dest.y > 0 ? move_amount : 0;
    }
    texture = textureUp;
    return { moveY, moveX };
}

Uint32 startTicks = SDL_GetTicks();
void Player::Update()
{
    auto elapsedTicks = SDL_GetTicks() - startTicks;
    int currentFrame = (elapsedTicks / 200) % 3;

    src.y = 0;
    src.x = currentFrame * 24;
}