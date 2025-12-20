#include "app.h"
#include "utils.hpp"

#include <saucer/app.hpp>

struct saucer_screen : saucer::cutils::opaque<saucer_screen, saucer::screen>
{
};

struct saucer_application : saucer::cutils::opaque<saucer_application, saucer::application>
{
};

struct saucer_application_options : saucer::cutils::opaque<saucer_application_options, saucer::application::options>
{
};
