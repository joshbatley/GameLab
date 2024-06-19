#pragma once

#include "SDL.h"
#include <functional>
#include <iostream>
#include <unordered_map>

namespace Input {
    enum EventType {
        KEY_PRESSED,
        MOUSE_MOVED,
    };

    enum InputAction {
        UP,
        DOWN,
        LEFT,
        RIGHT,

        COUNT,
    };

    enum InputState {
        INPUT_PRESENT = 1 << 7,
        INPUT_REPEAT = 1 << 3,
        INPUT_PRESS = 1 << 2,
        INPUT_UP = 1 << 1,
        INPUT_DOWN = 1 << 0,
    };

    struct MousePosition {
        int x;
        int y;
    };

    struct KeyEvent {
        uint8_t state;
        int time;
    };

    class Manager {
    public:
        Manager();
        void Update();
        void ProcessEvents(const SDL_Event *event);

        bool IsActionPressed(InputAction action) const;
        bool IsActionDown(InputAction action) const;
        bool IsActionUp(InputAction action) const;

        MousePosition GetMousePosition() const;

    private:
        std::unordered_map<SDL_Scancode, InputAction> _controlMap;
        MousePosition _mousePosition;
        KeyEvent _buttons[COUNT];
        std::vector<InputAction> _buttonsToClear;

        InputAction lookUpAction(SDL_Scancode code);
    };
}
