#pragma once

#include "utils/handle.hpp"
#include <saucer/scheme.hpp>

struct saucer_scheme_response : bindings::handle<saucer_scheme_response, saucer::scheme::handler::result_type>
{
};

struct saucer_scheme_request : bindings::handle<saucer_scheme_request, const saucer::scheme::request *>
{
};
