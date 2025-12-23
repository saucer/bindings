#pragma once

#include "permission.h"
#include "utils/opaque.hpp"

#include <saucer/permission.hpp>

struct saucer_permission_request : saucer::bindings::opaque<saucer_permission_request, //
                                                            std::shared_ptr<saucer::permission::request>>
{
};
