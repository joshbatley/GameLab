#include "Player.h"

Player::Player(std::string textureUp, std::string textureDown, std::string textureLeft, std::string textureRight, Input::Manager &inputManager) : _inputManager(inputManager)
{
    _textureUp = textureUp;
    _texture = _textureDown = textureDown;
    _textureLeft = textureLeft;
    _textureRight = textureRight;

    _dest.h = _dest.w = 32;
    _dest.y = _dest.x = 32;

    _src.w = _src.h = 24;
    _src.y = _src.x = 0;
}

std::pair<int, int> Player::Update(int level[15][15])
{
    const unsigned elapsedTicks = SDL_GetTicks() - _startTicks;
    const int currentFrame = (elapsedTicks / 200) % 3;

    _src.y = 0;
    _src.x = currentFrame * 24;

    if (_inputManager.IsActionPressed(Input::InputAction::UP)) {
        auto moveX = (_dest.x) / 32;
        auto moveY = (_dest.y - MOVE_AMOUNT) / 32;
        if (level[moveY][moveX] == 48) {
            _dest.y -= _dest.y > 0 ? MOVE_AMOUNT : 0;
        }
        _texture = _textureUp;
    }
    if (_inputManager.IsActionPressed(Input::InputAction::DOWN)) {
        auto moveX = (_dest.x) / 32;
        auto moveY = (_dest.y + MOVE_AMOUNT) / 32;
        if (level[moveY][moveX] == 48) {
            _dest.y += _dest.y + MOVE_AMOUNT < 480 ? MOVE_AMOUNT : 0;
        }
        _texture = _textureDown;
    }
    if (_inputManager.IsActionPressed(Input::InputAction::LEFT)) {
        auto moveX = (_dest.x - MOVE_AMOUNT) / 32;
        auto moveY = (_dest.y) / 32;
        if (level[moveY][moveX] == 48) {
            _dest.x -= _dest.x > 0 ? MOVE_AMOUNT : 0;
        }
        _texture = _textureLeft;
    }
    if (_inputManager.IsActionPressed(Input::InputAction::RIGHT)) {
        auto moveX = (_dest.x + MOVE_AMOUNT) / 32;
        auto moveY = (_dest.y) / 32;
        if (level[moveY][moveX] == 48) {
            _dest.x += _dest.x + MOVE_AMOUNT < 480 ? MOVE_AMOUNT : 0;
        }
        _texture = _textureRight;
    }
    return {_dest.x, _dest.y};
}

std::tuple<SDL_Rect, SDL_Rect, std::string> Player::Render()
{
    return {_src, _dest, _texture};
}
