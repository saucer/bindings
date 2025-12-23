#pragma once

#include <ranges>

namespace saucer::bindings
{
    template <std::ranges::sized_range T, typename V>
    void return_range(T &&, V *, std::size_t *);

    template <std::ranges::sized_range T, typename V>
    void return_range(std::optional<T>, V *, std::size_t *);
} // namespace saucer::bindings

#include "range.inl"
