#include "stash.h"
#include "utils.hpp"

#include <saucer/stash/stash.hpp>

struct saucer_stash : saucer::cutils::opaque<saucer_stash, saucer::stash<>>
{
};
