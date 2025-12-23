#pragma once

#include "icon.h"
#include "utils/opaque.hpp"

#include <saucer/icon.hpp>

struct saucer_icon : saucer::bindings::opaque<saucer_icon, saucer::icon>
{
};
