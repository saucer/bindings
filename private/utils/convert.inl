#pragma once

#include "convert.hpp"

#include <tuple>
#include <utility>
#include <string_view>

namespace saucer::bindings
{
    namespace detail
    {
        template <typename T>
        struct is_tuple;

        template <typename T>
        concept tuple = is_tuple<T>::value;
    } // namespace detail

    template <typename T>
    struct detail::is_tuple : std::false_type
    {
    };

    template <typename... Ts>
    struct detail::is_tuple<std::tuple<Ts...>> : std::true_type
    {
    };

    template <typename T>
    struct converter
    {
        template <typename U>
        static decltype(auto) convert(U &&value)
        {
            return std::forward<U>(value);
        };
    };

    template <>
    struct converter<std::string_view>
    {
        static auto convert(const std::string_view &value)
        {
            return std::make_tuple(value.data(), value.size());
        };
    };
} // namespace saucer::bindings
