#pragma once

#include "extract.hpp"
#include "convert.hpp"

#include <rebind/tuple.hpp>

#include <print>
#include <cstdlib>

namespace saucer::bindings
{
    namespace detail
    {
        template <std::size_t I = 0, tuple T>
            requires(I < std::tuple_size_v<T>)
        void extract_impl(T &&, std::size_t, void *, std::size_t *);

        template <std::size_t I = 0, tuple T>
            requires(I >= std::tuple_size_v<T>)
        void extract_impl(T &&, std::size_t, void *, std::size_t *);
    } // namespace detail

    template <std::size_t I, detail::tuple T>
        requires(I < std::tuple_size_v<T>)
    void detail::extract_impl(T &&tuple, std::size_t idx, void *result, std::size_t *size)
    {
        if (!result && !size)
        {
            return;
        }

        if (I < idx)
        {
            return extract_impl<I + 1>(std::forward<T>(tuple), idx, result, size);
        }

        using element = std::remove_reference_t<std::tuple_element_t<I, T>>;

        if constexpr (not std::is_trivially_copyable_v<element>)
        {
            std::println(stderr, "[saucer] The extracted value (idx: {}) is not trivially copyable! Be cautious...", I);
        }

        if (!result)
        {
            *size = sizeof(element);
            return;
        }

        if (*size < sizeof(element))
        {
            std::abort();
        }

        *reinterpret_cast<element *>(result) = std::get<I>(tuple);
    }

    template <std::size_t I, detail::tuple T>
        requires(I >= std::tuple_size_v<T>)
    void detail::extract_impl(T &&, std::size_t, void *, std::size_t *)
    {
        std::abort();
    }

    template <typename T>
    void extract(T &&value, std::size_t idx, void *result, std::size_t *size)
    {
        detail::extract_impl(rebind::to_tuple(value), idx, result, size);
    }
} // namespace saucer::bindings
