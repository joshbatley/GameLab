#pragma once

#include <typeindex>
#include <unordered_map>

namespace Engine {
    template<typename... Types>
    struct Resource {
        std::tuple<Types &...> data {};

        template<typename T = void>
        T &extract()
        {
            static_assert((std::is_same_v<T, void> && sizeof...(Types) > 1) || (std::disjunction_v<std::is_same<T, Types>...>), "Requested type not found in type list");
            if constexpr (sizeof...(Types) == 1) {
                return std::get<0>(data);
            } else {
                static_assert(!std::is_same_v<T, void>, "Template argument must be provided for multiple types");
                return std::get<T &>(data);
            }
        }

        std::tuple<Types &...> extract()
        {
            return data;
        }
    };


}// namespace Engine

namespace Resource {
    class Handler {
    public:
        template<typename T>
        void add(T &data)
        {
            if (_store.contains(typeid(T))) {
                throw std::logic_error("Only one instance of each component type is allowed");
            }
            _store[typeid(T)] = &data;
        }

        template<typename T>
        void add()
        {
            if (_store.contains(typeid(T))) {
                throw std::logic_error("Only one instance of each component type is allowed");
            }
            _store[typeid(T)] = new T();
        }


        template<typename T, typename... Rest>
        Engine::Resource<T, Rest...> get()
        {
            return Engine::Resource<T, Rest...> {.data = {*static_cast<T *>(_store[typeid(T)]), *static_cast<Rest *>(_store[typeid(Rest)])...}};
        }

    private:
        std::unordered_map<std::type_index, void *> _store;
    };
}// namespace Resource