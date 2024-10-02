#pragma once

#include "utils/handle.hpp"
#include <saucer/app.hpp>

struct saucer_application : bindings::handle<saucer_application, std::shared_ptr<saucer::application>>
{
};
