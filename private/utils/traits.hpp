#pragma once

namespace saucer::bindings
{
    template <typename T, template <typename...> typename C>
    struct is_container;

    template <typename T, template <typename...> typename C>
    concept container = is_container<T, C>::value;
} // namespace saucer::bindings

#include "traits.inl"
