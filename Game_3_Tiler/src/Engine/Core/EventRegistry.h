#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <vector>

class EventRegistry {
public:
    template<typename Event>
    void AddReader(std::function<void(Event)> readers)
    {
        _readers[typeid(Event)].push_back([readers](std::any eventData) {
            readers(std::any_cast<Event>(eventData));
        });
    }

    template<typename Event>
    void Send(Event eventData)
    {
        _queue.emplace_back<std::pair<std::type_index, std::any>>({typeid(Event), std::any(eventData)});
    }

    void Update()
    {
        auto currentQueue = std::move(_queue);
        _queue.clear();

        for (const auto &[type, event]: currentQueue) {
            if (_readers.find(type) != _readers.end()) {
                for (auto &listener: _readers[type]) {
                    listener(event);
                }
            }
        }
    }

private:
    std::map<std::type_index, std::vector<std::function<void(std::any)>>> _readers;
    std::vector<std::pair<std::type_index, std::any>> _queue;
};
