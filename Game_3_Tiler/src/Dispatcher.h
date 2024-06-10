#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <vector>

class Dispatcher {
public:
    std::map<std::type_index, std::vector<std::function<void(std::any)>>> eventListeners;
    std::vector<std::pair<std::type_index, std::any>> eventQueue;

    template<typename EventType>
    void AddEventListener(std::function<void(EventType)> listener)
    {
        eventListeners[typeid(EventType)].push_back([=](std::any eventData) {
            listener(std::any_cast<EventType>(eventData));
        });
    }

    template<typename EventType>
    void EnqueueEvent(EventType eventData)
    {
        eventQueue.push_back({typeid(EventType), std::any(eventData)});
    }

    void Update()
    {
        for (const auto &eventData: eventQueue) {
            if (eventListeners.find(eventData.first) != eventListeners.end()) {
                for (auto &listener: eventListeners[eventData.first]) {
                    listener(eventData.second);
                }
            }
        }
        eventQueue = {};
    }
};
