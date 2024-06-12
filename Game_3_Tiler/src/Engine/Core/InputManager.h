#pragma once

#include <SDL.h>
#include <functional>
#include <iostream>
#include <unordered_map>

namespace Input {
    enum InputAction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ACTION1,
        ACTION2,
        ACTION3,
        // META
        COUNT,
    };

    enum InputState {
        INPUT_PRESENT = 1 << 7,
        INPUT_PRESS = 1 << 2,// Event occurred
        INPUT_UP = 1 << 1,   // Event ended
        INPUT_DOWN = 1 << 0, // Event down
    };

    struct MousePosition {
        int x;
        int y;
    };

    struct KeyEvent {
        uint8_t state;
        int time;

        bool IsPressed() const
        {
            return state & INPUT_PRESS;
        }

        bool IsDown() const
        {
            return state & INPUT_DOWN;
        }

        bool IsUp() const
        {
            return state & INPUT_UP;
        }
    };

    class Manager {
    public:
        Manager();
        void Update();
        void ProcessEvents(bool *isRunning);
        bool IsActionPressed(InputAction action) const;
        bool IsActionDown(InputAction action) const;
        bool IsActionUp(InputAction action) const;
        MousePosition GetMousePosition() const;

    private:
        std::unordered_map<SDL_Scancode, InputAction> _controlMap;
        MousePosition _mousePosition;
        KeyEvent _buttons[COUNT];
        std::vector<InputAction> _buttonsToClear;
        void _processEvents(const SDL_Event *event);
    };
}