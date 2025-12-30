#pragma once

#include "traits.hpp"

#include <type_traits>

namespace saucer::bindings
{
    template <typename T, template <typename...> typename C>
    struct is_container : std::false_type
    {
    };

    template <template <typename...> typename C, typename... Ts>
    struct is_container<C<Ts...>, C> : std::true_type
    {
    };
} // namespace saucer::bindings

#include "traits.inl"
