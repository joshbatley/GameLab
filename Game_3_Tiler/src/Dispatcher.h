#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <typeindex>
#include <vector>

class Dispatcher {
public:
    template<typename Event>
    void AddEventReader(std::function<void(Event)> readers)
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
        for (const auto &[type, event]: _queue) {
            if (_readers.find(type) != _readers.end()) {
                for (auto &listener: _readers[type]) {
                    listener(event);
                }
            }
        }
        _queue.clear();
    }

private:
    std::map<std::type_index, std::vector<std::function<void(std::any)>>> _readers;
    std::vector<std::pair<std::type_index, std::any>> _queue;
};
