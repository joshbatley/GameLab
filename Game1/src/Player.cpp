#include "Player.h"
#include <iostream>

const int move_amount = 32;

Player::Player(SDL_Renderer* renderer, int start)
{
    texture = textureDown = Utils::LoadTex(renderer, pathDown.c_str());
    textureUp = Utils::LoadTex(renderer, pathUp.c_str());
    textureSide = Utils::LoadTex(renderer, pathSide.c_str());
    dest.h = dest.w = 32;
    dest.y = dest.x = start * 32;

    src.w = src.h = 24;
    src.y = src.x = 0;
}

Player::~Player()
{}

void Player::Render(SDL_Renderer* renderer)
{
    if (direction != -1) {
        SDL_RenderCopy(renderer, texture, &src, &dest);
    } else {
        SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, nullptr, SDL_FLIP_HORIZONTAL);
    }
}

void Player::MoveRight(std::vector<std::vector<int>>* level)
{
    auto moveY = (dest.y) / 32;
    auto moveX = (dest.x + move_amount) / 32;
    if (level->at(moveX).at(moveY) == 0) {
        dest.x += dest.x + move_amount < 480 ? move_amount : 0;
    }

    texture = textureSide;
    direction = 1;
}

void Player::MoveLeft(std::vector<std::vector<int>>* level)
{
    auto moveY = (dest.y) / 32;
    auto moveX = (dest.x - move_amount) / 32;
    if (level->at(moveX).at(moveY) == 0) {
        dest.x -= dest.x > 0 ? move_amount : 0;
    }
    direction = -1;
    texture = textureSide;
}

void Player::MoveDown(std::vector<std::vector<int>>* level)
{
    auto moveY = (dest.y + move_amount) / 32;
    auto moveX = (dest.x) / 32;
    if (level->at(moveX).at(moveY) == 0) {
        dest.y += dest.y + move_amount < 480 ? move_amount : 0;
    }
    texture = textureDown;
    direction = 0;
}

void Player::MoveUp(std::vector<std::vector<int>>* level)
{
    auto moveY = (dest.y - move_amount) / 32;
    auto moveX = (dest.x) / 32;
    if (level->at(moveX).at(moveY) == 0) {
        dest.y -= dest.y > 0 ? move_amount : 0;
    }
    texture = textureUp;
    direction = 0;
}

Uint32 startTicks = SDL_GetTicks();
void Player::Update()
{
    Uint32 elapsedTicks = SDL_GetTicks() - startTicks;
    int currentFrame = (elapsedTicks / 200) % 3;

    src.y = 0;
    src.x = currentFrame * 24;
}