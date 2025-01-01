#pragma once

#include "utils/handle.hpp"
#include <saucer/scheme.hpp>

struct saucer_scheme_response : bindings::handle<saucer_scheme_response, saucer::scheme::response>
{
};

struct saucer_scheme_request : bindings::handle<saucer_scheme_request, saucer::scheme::request>
{
};

struct saucer_scheme_executor : bindings::handle<saucer_scheme_executor, saucer::scheme::executor>
{
};
