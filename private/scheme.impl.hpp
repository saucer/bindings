#pragma once

#include "scheme.h"
#include "utils/opaque.hpp"

#include <saucer/scheme.hpp>

struct saucer_scheme_executor : saucer::bindings::opaque<saucer_scheme_executor, saucer::scheme::executor>
{
};

struct saucer_scheme_request : saucer::bindings::opaque<saucer_scheme_request, saucer::scheme::request>
{
};

struct saucer_scheme_response : saucer::bindings::opaque<saucer_scheme_response, saucer::scheme::response>
{
};
