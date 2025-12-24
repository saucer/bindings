#pragma once

#include <ranges>
#include <vector>

namespace saucer::bindings
{
    template <std::ranges::sized_range T, typename V>
    void return_range(T &&, V *, std::size_t *);

    template <std::ranges::sized_range T, typename V>
    void return_range(std::optional<T>, V *, std::size_t *);

    template <std::ranges::sized_range T>
    auto vectorize(T &&);
} // namespace saucer::bindings

#include "range.inl"
