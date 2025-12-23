#pragma once

namespace saucer::bindings
{
    template <typename CRTP, typename T>
    struct opaque
    {
        T value;

      public:
        T *ptr() noexcept;
        operator CRTP *() noexcept;

      public:
        T &operator*() noexcept;
        T *operator->() noexcept;

      public:
        static CRTP *from(T &&);

      public:
        template <typename... Ts>
        static CRTP *make(Ts &&...);
    };
} // namespace saucer::bindings

#include "opaque.inl"
