#pragma once

#include <filesystem>

namespace saucer::bindings
{
    namespace fs = std::filesystem;

    fs::path u8path(const char *);
} // namespace saucer::bindings

#include "wide.inl"
