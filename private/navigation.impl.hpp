#pragma once

#include "navigation.h"
#include "utils/opaque.hpp"

#include <saucer/navigation.hpp>

struct saucer_navigation : saucer::bindings::opaque<saucer_navigation, const saucer::navigation *>
{
};
