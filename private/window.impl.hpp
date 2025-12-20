#include "window.h"
#include "utils.hpp"

#include <saucer/window.hpp>

struct saucer_window : saucer::cutils::opaque<saucer_window, std::shared_ptr<saucer::window>>
{
};
