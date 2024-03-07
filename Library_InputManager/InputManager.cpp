#include "InputManager.h"

void InputManager::Subscribe(EventType type, std::function<void()> callback) {
    eventListeners[type].push_back(callback);
}

void InputManager::ProcessEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                dispatchEvent(KEY_PRESSED);
            case SDL_MOUSEMOTION:
                mousePosition.x = event.motion.x;
                mousePosition.y = event.motion.y;
                dispatchEvent(MOUSE_MOVED);
                break;
        }
    }
}

void InputManager::dispatchEvent(EventType eventType) {
    for (auto& listener : eventListeners[eventType]) {
        listener();
    }
}

bool InputManager::IsActionPressed(InputAction action) {
    auto keycodes = actionMap[action];
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);

    for (const auto& keycode : keycodes) {
        if (keyStates[keycode]) {
            return true;
        }
    }

    return false;
}

MousePosition InputManager::GetMousePosition() {
    return mousePosition;
}
