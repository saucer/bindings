#pragma once

#include "opaque.hpp"

#include <utility>

namespace saucer::bindings
{
    template <typename CRTP, typename T>
    T *opaque<CRTP, T>::ptr() noexcept
    {
        return std::addressof(value);
    }

    template <typename CRTP, typename T>
    opaque<CRTP, T>::operator CRTP *() noexcept
    {
        return static_cast<CRTP *>(this);
    }

    template <typename CRTP, typename T>
    T &opaque<CRTP, T>::operator*() noexcept
    {
        return *ptr();
    }

    template <typename CRTP, typename T>
    T *opaque<CRTP, T>::operator->() noexcept
    {
        return ptr();
    }

    template <typename CRTP, typename T>
    CRTP *opaque<CRTP, T>::from(T &&value)
    {
        return new CRTP{std::move(value)};
    }

    template <typename CRTP, typename T>
    template <typename... Ts>
    CRTP *opaque<CRTP, T>::make(Ts &&...args)
    {
        return new CRTP{T{std::forward<Ts>(args)...}};
    }
} // namespace saucer::bindings
