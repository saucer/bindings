#pragma once

#include "app.h"
#include "utils/opaque.hpp"

#include <saucer/app.hpp>

struct saucer_screen : saucer::bindings::opaque<saucer_screen, saucer::screen>
{
};

struct saucer_application : saucer::bindings::opaque<saucer_application, saucer::application>
{
};

struct saucer_application_options : saucer::bindings::opaque<saucer_application_options, saucer::application::options>
{
};
