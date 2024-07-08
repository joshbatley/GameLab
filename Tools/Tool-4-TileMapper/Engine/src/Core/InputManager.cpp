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
          {SDL_SCANCODE_SPACE, InputAction::ACTION3},
          {SDL_SCANCODE_1, InputAction::NUM1},
          {SDL_SCANCODE_2, InputAction::NUM2},
          {SDL_SCANCODE_3, InputAction::NUM3}};
    }

    void Manager::Update()
    {
        for (const auto btn: _buttonsToClear) {
            _buttons[btn].state &= ~(INPUT_PRESS | INPUT_UP);
        }
        _buttonsToClear.clear();
    }

    void Manager::ProcessEvents(bool *isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    *isRunning = false;
                    break;
            }
            ProcessEvents(&event);
        }
    }

    void Manager::ProcessEvents(const SDL_Event *event)
    {
        switch (event->type) {
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYUP:
            case SDL_KEYDOWN: {
                const auto IsMouseEvent = event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP;
                const auto action = IsMouseEvent ? InputAction::ACTION1 : _controlMap[event->key.keysym.scancode];
                const bool down = event->type == SDL_KEYDOWN || event->type == SDL_MOUSEBUTTONDOWN;
                uint8_t newState = INPUT_PRESENT;

                if (down) {
                    if (!_buttons[action].IsDown()) {
                        newState |= INPUT_PRESS;
                    }
                    newState |= INPUT_DOWN;
                } else {
                    newState |= INPUT_UP;
                }

                if (newState & (INPUT_PRESS | INPUT_UP)) {
                    _buttonsToClear.push_back(action);
                }

                _buttons[action].state = newState;
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