#ifndef LIBRARY_INPUTMANAGER_H
#define LIBRARY_INPUTMANAGER_H

#include "SDL.h"
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

enum EventType {
    KEY_PRESSED,
    MOUSE_MOVED,
};

enum InputAction {
    Up,
    Down,
    Left,
    Right,
};

struct MousePosition {
    int x;
    int y;
};


class InputManager {
public:
    void Subscribe(EventType type, std::function<void()> callback);
    void ProcessEvents();
    bool IsActionPressed(InputAction key);
    MousePosition GetMousePosition();

private:
    std::unordered_map<EventType, std::vector<std::function<void()>>> eventListeners;
    std::unordered_map<InputAction, std::vector<SDL_KeyCode>> actionMap;
    MousePosition mousePosition;

    void dispatchEvent(EventType eventType);
};

#endif// LIBRARY_INPUTMANAGER_H
