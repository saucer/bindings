#pragma once

#include "url.h"
#include "utils/opaque.hpp"

#include <saucer/url.hpp>

struct saucer_url : saucer::bindings::opaque<saucer_url, saucer::url>
{
};
