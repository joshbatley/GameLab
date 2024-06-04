#include "InputManager.h"

namespace Input {
    Manager::Manager()
        : _mousePosition(), _buttons {}
    {
        _controlMap = {
          {SDL_SCANCODE_UP, InputAction::UP},
          {SDL_SCANCODE_DOWN, InputAction::DOWN},
          {SDL_SCANCODE_LEFT, InputAction::LEFT},
          {SDL_SCANCODE_RIGHT, InputAction::RIGHT},
          {SDL_SCANCODE_W, InputAction::UP},
          {SDL_SCANCODE_S, InputAction::DOWN},
          {SDL_SCANCODE_A, InputAction::LEFT},
          {SDL_SCANCODE_D, InputAction::RIGHT},
          {SDL_SCANCODE_Q, InputAction::ACTION1},
          {SDL_SCANCODE_E, InputAction::ACTION2},
          {SDL_SCANCODE_SPACE, InputAction::ACTION3}};
    }

    void Manager::Update()
    {
        for (const auto btn: _buttonsToClear) {
            _buttons[btn].state &= ~(INPUT_PRESS | INPUT_UP);
        }
        _buttonsToClear.clear();
    }

    void Manager::ProcessEvents(const SDL_Event *event)
    {
        const auto now = std::time(nullptr);
        switch (event->type) {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYUP:
            case SDL_KEYDOWN: {
                const auto IsMouseEvent = event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP;
                const auto action = IsMouseEvent ? InputAction::ACTION1 : _controlMap[event->key.keysym.scancode];
                const bool down = event->type == SDL_KEYDOWN || event->type == SDL_MOUSEBUTTONDOWN;
                uint8_t newstate = INPUT_PRESENT;
                _buttons[action].time = now;

                if (down) {
                    if (!_buttons[action].IsDown()) {
                        newstate |= INPUT_PRESS;
                    }
                    newstate |= INPUT_DOWN;
                } else {
                    newstate |= INPUT_UP;
                }

                if (newstate & (INPUT_PRESS | INPUT_UP)) {
                    _buttonsToClear.push_back(action);
                }

                _buttons[action].state = newstate;
                break;
            }
            case SDL_MOUSEMOTION:
                _mousePosition.x = event->motion.x;
                _mousePosition.y = event->motion.y;
                break;
            default:
                break;
        }
    }

    bool Manager::IsActionPressed(const InputAction action) const
    {
        return _buttons[action].IsPressed();
    }

    bool Manager::IsActionDown(const InputAction action) const
    {
        return _buttons[action].IsDown();
    }

    bool Manager::IsActionUp(const InputAction action) const
    {
        return _buttons[action].IsUp();
    }

    MousePosition Manager::GetMousePosition() const
    {
        return _mousePosition;
    }
}