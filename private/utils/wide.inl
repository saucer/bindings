#pragma once

#include "wide.hpp"

#ifdef _WIN32
#include <saucer/win32.utils.hpp>
#endif

namespace saucer::bindings
{
    inline fs::path u8path(const char *path)
    {
#ifdef _WIN32
        return fs::path{utils::widen(path)};
#else
        return fs::path{path};
#endif
    }
} // namespace saucer::bindings
