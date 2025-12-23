#pragma once

#include "stash.h"
#include "utils/opaque.hpp"

#include <saucer/stash/stash.hpp>

struct saucer_stash : saucer::bindings::opaque<saucer_stash, saucer::stash>
{
};
