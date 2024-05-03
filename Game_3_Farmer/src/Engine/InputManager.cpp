#include "InputManager.h"

namespace Input {
    Manager::Manager() : _mousePosition(), _buttons{}
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
            {SDL_SCANCODE_SPACE, InputAction::ACTION3}
        };
    }

    void Manager::Update()
    {
        for (const auto btn: _buttonsToClear) {
            _buttons[btn].state &= ~(INPUT_PRESS | INPUT_UP | INPUT_DOWN);
        }
        _buttonsToClear.clear();
    }

    void Manager::ProcessEvents(const SDL_Event *event)
    {
        const auto now = std::time(nullptr);
        switch (event->type) {
            case SDL_KEYUP:
            case SDL_KEYDOWN: {
                const auto action = _controlMap[event->key.keysym.scancode];
                const bool repeat = event->key.repeat;
                const bool down = event->type == SDL_KEYDOWN;
                uint8_t newstate = INPUT_PRESENT;
                _buttons[action].time = now;

                if (down) {
                    if (repeat) {
                        newstate |= INPUT_REPEAT;
                    } else {
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

    InputAction Manager::lookUpAction(const SDL_Scancode code)
    {
        return _controlMap[code];
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

    bool Manager::IsActionRepeating(const InputAction action) const
    {
        return _buttons[action].IsRepeating();
    }

    MousePosition Manager::GetMousePosition() const
    {
        return _mousePosition;
    }
}