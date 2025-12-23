#pragma once

#include <type_traits>

namespace saucer::bindings
{
    template <auto From, auto To>
    struct map;

    template <auto From, typename To>
    using map_enum = map<From, std::type_identity<To>{}>;

    template <typename... Ts>
    struct map_events
    {
        struct impl;

      public:
        template <typename F, typename T, typename U>
        static auto on(F &&visitor, T &instance, const U &event, bool clearable);

      public:
        template <typename F, typename T, typename U>
        static auto once(F &&visitor, T &instance, const U &event);
    };
} // namespace saucer::bindings

#include "map.inl"
