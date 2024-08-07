#pragma once

#include "utils/handle.hpp"
#include <saucer/stash/stash.hpp>

struct saucer_stash : bindings::handle<saucer_stash, saucer::stash<>>
{
};
