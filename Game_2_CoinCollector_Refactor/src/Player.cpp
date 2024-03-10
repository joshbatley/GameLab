#include "Player.h"

Player::Player(SDL_Texture *textureUp, SDL_Texture *textureDown, SDL_Texture *textureLeft, SDL_Texture *textureRight, Input::Manager &inputManager) : _inputManager(inputManager) {
    _textureUp = textureUp;
    _texture = _textureDown = textureDown;
    _textureLeft = textureLeft;
    _textureRight = textureRight;

    _dest.h = _dest.w = 32;
    _dest.y = _dest.x = 32;

    _src.w = _src.h = 24;
    _src.y = _src.x = 0;
}

bool Player::HandleMovementPause() {
    static int moveTimer = 0;
    static bool movePaused = false;

    if (!movePaused) {
        movePaused = true;
    }

    moveTimer++;
    if (moveTimer >= 10) {
        movePaused = false;
        moveTimer = 0;
    }

    return movePaused;
}

void Player::Update() {
    const unsigned elapsedTicks = SDL_GetTicks() - _startTicks;
    const int currentFrame = (elapsedTicks / 200) % 3;

    _src.y = 0;
    _src.x = currentFrame * 24;

    if (HandleMovementPause()) {
        return;
    }

    if (_inputManager.IsActionPressed(Input::InputAction::UP)) {
        _dest.y -= _dest.y > 0 ? MOVE_AMOUNT : 0;
        _texture = _textureUp;
        return;
    }
    if (_inputManager.IsActionPressed(Input::InputAction::DOWN)) {
        _dest.y += _dest.y + MOVE_AMOUNT < 480 ? MOVE_AMOUNT : 0;
        _texture = _textureDown;
        return;
    }
    if (_inputManager.IsActionPressed(Input::InputAction::LEFT)) {
        _dest.x -= _dest.x > 0 ? MOVE_AMOUNT : 0;
        _texture = _textureLeft;
        return;
    }
    if (_inputManager.IsActionPressed(Input::InputAction::RIGHT)) {
        _dest.x += _dest.x + MOVE_AMOUNT < 480 ? MOVE_AMOUNT : 0;
        _texture = _textureRight;
        return;
    }
}

std::tuple<SDL_Rect, SDL_Rect, SDL_Texture *> Player::Render() {
    return {_src, _dest, _texture};
}
