#pragma once

#include "window.h"
#include "utils/opaque.hpp"

#include <saucer/window.hpp>

struct saucer_window : saucer::bindings::opaque<saucer_window, std::shared_ptr<saucer::window>>
{
};
