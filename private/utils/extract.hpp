#pragma once

#include <cstddef>

namespace saucer::bindings
{
    template <typename T>
    void extract(T &&, std::size_t, void *, std::size_t *);
}

#include "extract.inl"
