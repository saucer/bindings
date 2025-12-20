#pragma once

#include <ranges>
#include <variant>

namespace saucer::cutils
{
    template <typename T, typename U>
    struct opaque
    {
        // TODO: Is `view` required?
        // TODO: Initial idea for it was to re-obtain an opaque from a reference, but it seems that might not be
        // TODO: required as I can always keep the original pointer the user passed around somehow...
        std::variant<U, U *> value;

      public:
        U *ptr();

      public:
        U &operator*() noexcept;
        U *operator->() noexcept;

      public:
        static T *view(U &);
        static T *from(U &&);

      public:
        template <typename... Ts>
        static T *make(Ts &&...);
    };

    template <typename T>
    struct converter;

    template <std::ranges::sized_range T, typename V>
    void return_range(T &&, V *, std::size_t *);

    template <auto From, typename To>
    struct map;

    template <typename... Ts>
    struct event_mapper
    {
        struct impl;

      public:
        template <typename F, typename T, typename U>
        static auto on(F &&visitor, T &instance, const U &event, bool clearable);

      public:
        template <typename F, typename T, typename U>
        static auto once(F &&visitor, T &instance, const U &event);
    };
} // namespace saucer::cutils

#include "utils.inl"
